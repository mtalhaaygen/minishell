/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:57:34 by maygen            #+#    #+#             */
/*   Updated: 2023/09/06 17:11:16 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_access(char *args)
{
	char	**command_paths;
	char	*pathenv;
	char	*command;
	int		i;

	i = -1;
	pathenv = ft_getenv("PATH"); // fullden çek env yi
	if (!pathenv)
		printf("tsh: %s: No such file or directory", args); // update $? =127
	command_paths = ft_split(pathenv, ':');
	if (args[0] == '/' || (args[1] == '/' && args[0] == '.'))
		return (args);
	args = ft_strjoin("/", args);
	while (command_paths[++i])
	{
		command = ft_strjoin(command_paths[i], args);
		if (access(command, R_OK | X_OK) == 0)
			break ;
	}
	if (!command_paths[i])
	{
		printf("tsh: %s: command not found\n", args + 1);
		exit(127);
	}
	return (command);
}

void	ft_executor(t_node *nodes)
{
	int		status;
	char	*bin_command;
	int		i;

	i = -1;
	while (++i < g_va->process_count)
	{
		if (nodes[i].args[0] && !(status = is_other_builtin(nodes[i])))
		{
			g_va->pid = fork();
			if (g_va->pid == 0)
			{
				ft_syntax_error(nodes);
				ft_process_merge(i);
				is_redirection(nodes, i);
				if ((status = is_builtin(nodes[i].args)))
					run_builtin(status, nodes[i]);
				bin_command = ft_access(nodes[i].args[0]);
				if (execve(bin_command, nodes[i].args, g_va->full))
					ft_perror(bin_command);
				exit (127); // OK
			}
			else if (g_va->pid < 0) 
				return (perror("tsh: executor fork error")); // update $? =1
		}
		run_other_builtin(status, nodes[i]);
	}
	pipe_close();
	i = -1;
	status = -1;
	while (++i < g_va->process_count)
		waitpid(g_va->pid, &status, 0);
	if (WIFEXITED(status) && g_va->err_number >= 0)
		g_va->err_number = WEXITSTATUS(status);
	add_dollar_question_mark();
}

void	exec_start(t_node *nodes)
{
	t_process	*process;
	int			i;

	if (!g_va->nodes[g_va->process_count - 1].args[0])
		g_va->process_count -= 1;
	if (g_va->process_count > 1)
	{
		process = ft_calloc(g_va->process_count - 1, sizeof(t_process));
		if (!process)
			return ;
		i = -1;
		while (++i < g_va->process_count - 1)
		{
			if (pipe(process[i].fd) == -1)
				perror("tsh: pipe not created"); // update $? = 1
		}
		g_va->process = process;
	}
	exec_select(nodes);
}

void	exec_select(t_node *nodes)
{
	int		i;
	int		th;
	int		flag;
	int		status;

	th = -1;
	while (++th < g_va->process_count)
	{
		i = -1;
		flag = 0;
		if (ft_strcmp("<<", nodes[th].args[0]) && nodes[th].args[1] == NULL)
			break ;
		while (nodes[th].args[++i] != NULL && nodes[th].args[i]) 
		{
			if (flag > 1)
				i = i - 1;
			status = ft_strcmp("<<", nodes[th].args[i]);
			if (status == 1)
			{
				flag++;
				ft_executor_heredoc(nodes, th, i, flag);
			}
			else if (status == -1)
				break ;
		}
	}
	ft_executor(nodes);
}

/*
aşağıdaki caselerin hepsi çalışıyor, yalnızca üç	 heredoc bir node içerisinde olursa patlıyor
cat <<EOF1 <<EOF2
> first here-doc
> EOF1
> second here-doc
> EOF2
*/
/*
bash-3.2$ cat <<E1 | cat <<E2
> DENEME
> E1
> DENEME2
> E2
DENEME2
*/
/*
bash-3.2$ ls -la | cat << EOF
> DDFGH
> EOF
DDFGH
*/
/*
bash-3.2$ cat << EOF | ls
> deneme
> EOF
Makefile        executor        minishell.h
README.md       lib             parser
builtin         main.c          talha.txt
*/
/*
bash-3.2$ cat << EOF | grep ali
> deneme
> aliço
ls << s
> aligo
> alimo
> EOF
aliço
aligo
alimo
*/