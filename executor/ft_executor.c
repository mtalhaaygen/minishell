/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:58:35 by maygen            #+#    #+#             */
/*   Updated: 2023/08/05 16:28:45 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_executor(Node *nodes, char **envp)
{
	int status;
	char *bin_command;
	pid_t ret;
	int i;
	
	i = -1;
	while (++i < gv.process_count) // kaç tane komut varsa (ve bu komutlar builtin değilse) o kadar fork yapılıyor ve exec e gönderiliyor
	{
		status = is_builtin(nodes[i].args[0]); // komutun ilk argümanı builtin mi değil mi ?
		if (!status)
		{
			ret = fork();
			if (ret == 0)
			{
				bin_command = ft_strjoin("/bin/", nodes[i].args[0]);
				if (execve(bin_command, nodes[i].args, envp))
					perror("execve error ");
				exit(1);
			}
			else if (ret < 0) 
			{
				perror("fork error ");
				return ;
			}
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