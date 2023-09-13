/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 14:53:10 by maygen            #+#    #+#             */
/*   Updated: 2023/09/13 15:50:07 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_pwd(void)
{
	char	*s;

	s = getcwd(NULL, 0);
	if (!s)
	{
		perror("tsh: pwd getcwd error");
		exit(1);
	}
	else
		printf("%s\n", s);
	free(s);
	exit(0);
}

void	run_cd(t_node node)
{
	char	*s;

	if (node.arg_count != 1 && node.args[1][0] != '~')
	{
		if (chdir(node.args[1]) != 0)
		{
			printf("tsh: cd: %s: No such file or directory\n", node.args[1]);
			question_mark_update(ft_strdup("?=1"), -1);
		}
	}
	else
	{
		s = getenv("HOME");
		if (s && *s)
		{
			if (chdir(s))
			{
				perror("tsh: cd chdir error");
				question_mark_update(ft_strdup("?=1"), -1);
			}
		}
	}
}
