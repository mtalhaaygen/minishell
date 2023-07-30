/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:52:56 by maygen            #+#    #+#             */
/*   Updated: 2023/07/30 15:58:22 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_builtin(int status)
{
	if (status == CD)
		printf("cd çalıştır");
	else if (status == ENV)
		printf("env çalıştır");
	else if (status == PWD)
		printf("pwd çalıştır");
	else if (status == EXIT)
		printf("exit çalıştır");
	else if (status == ECHO)
		printf("echo çalıştır");
	else if (status == UNSET)
		printf("unset çalıştır");
	else if (status == EXPORT)
		printf("export çalıştır");
	else
		printf("command not builtin");
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
