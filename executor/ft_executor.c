/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:58:35 by maygen            #+#    #+#             */
/*   Updated: 2023/08/17 14:21:00 by maygen           ###   ########.fr       */
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
		perror("getenv");
	command_paths = ft_split(pathenv, ':');
	args = ft_strjoin("/", args);
	while (command_paths[i])
	{
		command = ft_strjoin(command_paths[i], args);
		if (access(command, R_OK) == 0)
			break;
		i++;
	}
	return (command);
}

void	ft_executor(Node *nodes, char **envp)
{
	int status;
	char *bin_command;
	int i;

	i = -1;
	while (++i < gv.process_count)
	{
		//; // fork altında çalıştırılmayacak olan builtinlerden mi status bunu tutuyor
		if (!(status = is_other_builtin(nodes[i].args[0])))
		{
			gv.pid = fork();
			if (gv.pid == 0)
			{
				ft_process_merge(i);
				is_redirection(nodes, i);
				if ((status = is_builtin(nodes[i].args[0])))
					run_builtin(status, nodes[i]);
				bin_command = ft_access(nodes[i].args[0]);
				if (execve(bin_command, nodes[i].args, envp))
					perror("execve perror ");
			}
			else if (gv.pid < 0) 
				return (perror("fork error "));
		}
		run_other_builtin(status, nodes[i]);
	}
	pipe_close();
	i = -1;
	while (++i < gv.process_count)
		waitpid(gv.pid, NULL, 0);
}

void	exec_start(Node *nodes, char **envp)
{
	if (gv.process_count > 1)
	{
		s_process	*process;
		int			i;

		process = ft_calloc(gv.process_count - 1, sizeof(s_process));
		if (!process)
			return ;
		i = -1;
		while (++i < gv.process_count - 1)
		{
			if (pipe(process[i].fd) == -1)
				perror("pipe not created");
		}
		gv.process = process;
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
	while (++th < gv.process_count)
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
aşağıdaki caselerin hepsi çalışıyor, yalnızca üç heredoc bir node içerisinde olursa patlıyor
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