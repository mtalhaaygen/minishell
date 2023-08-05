/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:52:56 by maygen            #+#    #+#             */
/*   Updated: 2023/08/05 15:42:46 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_builtin(int status, Node node)
{
	if (status == CD)
		run_cd(node);
	else if (status == ENV)
		printf("env çalıştır\n");
	else if (status == PWD)
		run_pwd();
	else if (status == EXIT)
		printf("exit çalıştır\n");
	else if (status == ECHO)
		run_echo(node);
	else if (status == UNSET)
		printf("unset çalıştır\n");
	else if (status == EXPORT)
		printf("export çalıştır\n");
	else
		printf("command not builtin\n");
}

int	is_builtin(char *command)
{
	if (ft_strcmp(command, "cd"))
		return (CD);
	if (ft_strcmp(command, "env"))
		return (ENV);
	if (ft_strcmp(command, "pwd"))
		return (PWD);
	if (ft_strcmp(command, "exit"))
		return (EXIT);
	if (ft_strcmp(command, "echo"))
		return (ECHO);
	if (ft_strcmp(command, "unset"))
		return (UNSET);
	if (ft_strcmp(command, "export"))
		return (EXPORT);
	return (0);
}
