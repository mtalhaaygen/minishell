/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 14:53:10 by maygen            #+#    #+#             */
/*   Updated: 2023/08/20 14:53:11 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_pwd(void)
{
	char *s;

	s = getcwd(NULL, 0);
	if (!s)
		perror("pwd getcwd error ");
	else
		printf("%s\n",s);
	free(s);
	exit(0);
}

void	run_cd(Node node)
{
	char	*s;

	if (node.arg_count != 1)
	{
		if (chdir(node.args[1]) != 0)
			perror("cd error ");
	}
	else
	{
		s = getenv("HOME");
		if (s && *s)
		{
			if (chdir(s))
				perror("chdir error ");
		}
	}
}
