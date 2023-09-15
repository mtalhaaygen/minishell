/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:13:23 by maygen            #+#    #+#             */
/*   Updated: 2023/09/15 17:40:32 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_err(char *str, char *args)
{
	printf("tsh: %s: %s\n", args, str);
	exit(127);
}

char	*ft_access(char *args)
{
	char	**command_paths;
	char	*pathenv;
	char	*command;
	int		i;

	i = -1;
	if (!args[0])
		exit(0);
	pathenv = ft_getenv("PATH");
	if (!pathenv)
		ft_print_err("No such file or directory", args);
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
		ft_print_err("command not found", args + 1);
	return (command);
}
