/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:57:34 by maygen            #+#    #+#             */
/*   Updated: 2023/08/26 15:27:10 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_access(char *args)
{
	char	**command_paths;
	char	*pathenv;
	char	*command;
	int		i;

	i = 0;
	pathenv = getenv("PATH");
	if (!pathenv)
		perror("tsh: PATH environment variable does not exist");
	command_paths = ft_split(pathenv, ':');
	if (args[0] == '/' || (args[1] == '/' && args[0] == '.'))
		return (args);
	args = ft_strjoin("/", args);
	while (command_paths[i])
	{
		command = ft_strjoin(command_paths[i], args);
		if (access(command, R_OK | X_OK) == 0)
			break;
		i++;
	}
	if (!command_paths[i])
	{
		printf("tsh: %s: command not found\n", args + 1);
		exit(1);
	}
	return (command);
}

void	ft_executor(Node *nodes, char **envp)
{
	int status;
	char *bin_command;
	int i;

	i = -1;
	while (++i < g_va->process_count)
	{
		if (nodes[i].args[0] && !(status = is_other_builtin(nodes[i])))
		{
			g_va->pid = fork();
			if (g_va->pid == 0)
			{
				ft_process_merge(i);
				is_redirection(nodes, i);
				if ((status = is_builtin(nodes[i].args)))
					run_builtin(status, nodes[i]);
				bin_command = ft_access(nodes[i].args[0]);
				if (execve(bin_command, nodes[i].args, envp))
					perror("tsh: execve error");
				exit (1);
			}
			else if (g_va->pid < 0) 
				return (perror("tsh: executor fork error"));
		}
		run_other_builtin(status, nodes[i]);
	}
	pipe_close();
	i = -1;
	int status1 = -1;
	while (++i < g_va->process_count)
		waitpid(g_va->pid, &status1, 0);
	rm_heredoc();
	if (WIFEXITED(status1))
	{
		g_va->err_number = WEXITSTATUS(status1);
		// printf("*%d*\n", g_va->err_number);
	}
}

void	exec_start(Node *nodes, char **envp)
{
	if (!g_va->nodes[g_va->process_count - 1].args[0])
		g_va->process_count -= 1;
	if (g_va->process_count > 1)
	{
		s_process	*process;
		int			i;

		process = ft_calloc(g_va->process_count - 1, sizeof(s_process));
		if (!process)
			return ;
		i = -1;
		while (++i < g_va->process_count - 1)
		{
			if (pipe(process[i].fd) == -1)
				perror("tsh: pipe not created");
		}
		g_va->process = process;
	}
	exec_select(nodes, envp);
}

void	exec_select(Node *nodes, char **envp)
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
		while (nodes[th].args[++i]) 
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
	ft_executor(nodes, envp);
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
> aligo
> alimo
> EOF
aliço
aligo
alimo
*/