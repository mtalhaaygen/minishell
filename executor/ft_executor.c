/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:58:35 by maygen            #+#    #+#             */
/*   Updated: 2023/08/11 17:22:00 by maygen           ###   ########.fr       */
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
	pid_t ret;
	int i;
	
	i = -1;
	while (++i < gv.process_count)
	{
		// is_redirection ile heredoc dışındaki yönlendirmeler için fd change işlemleri yapılacak
		dup2();
		status = is_builtin(nodes[i].args[0]);
		if (!status)
		{
			ret = fork();
			if (ret == 0)
			{
				bin_command = ft_access(nodes[i].args[0]);
				if (execve(bin_command, nodes[i].args, envp))
					perror("execve perror ");
				exit(1);
			}
			else if (ret < 0) 
				return (perror("fork error "));
		}
		else
			run_builtin(status, nodes[i]);
	}
	if (ret > 0)
		waitpid(ret, NULL, 0);
}

void	exec_start(Node *nodes, char **envp)
{
	if (gv.process > 1)
	{
		int			i;
		s_process	*process;

		process = ft_calloc(gv.process_count , sizeof(s_process));
		if (!process)
			return ;
		i = -1;
		while (++i < gv.process_count)
		{
			if (pipe(&process[i].fd[2]) == -1)
				perror("pipe not created");
		}
		gv.process = process;
	}
	exec_select(nodes, envp);
}

void	exec_select(Node *nodes, char **envp) //  eğer komut içerisinde heredoc varsa ft_executor_heredoc yoksa ft_executor çalışacak
{
	int	i;
/* 
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
	if (gv.process_count == 1) //bir process varsa, gelecekte sadece ilk node değil tüm nodelar arasında heredoc aranacak 
	{
		i = -1;
		while (nodes[0].args[++i])
		{
			if (ft_strcmp("<<", nodes[0].args[i]))
			{
				ft_executor_heredoc(nodes, i);
				return;
			}
		}
	}
	ft_executor(nodes, envp);
}