/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:58:35 by maygen            #+#    #+#             */
/*   Updated: 2023/08/06 15:01:42 by maygen           ###   ########.fr       */
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
/*
void	ft_executor(Node *nodes)
{
	int status;
	
	status = is_builtin(nodes->args[0]);
	if (status == 0)
	{
		printf("execve\n");
		//execve komutu process i sonlandırdığından
		//pipe + 1 kadar fork yapılacak, tüm child processlerin pid i 0 oluyor
		//child processlerde execve komutu çalıştırılacak
	}
	else
		run_builtin(status, nodes[0]);
}
*/