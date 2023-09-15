/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:55:10 by maygen            #+#    #+#             */
/*   Updated: 2023/09/15 18:02:24 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo_param_checker(char *str)
{
	int	i;

	i = 2;
	if (!str)
		return (0);
	if (!str[0] || str[0] != '-')
		return (0);
	if (!str[1] || str[1] != 'n')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	run_echo(t_node node)
{
	int	i;

	i = 1;
	if (node.args[i] == NULL)
	{
		ft_putstr_fd("\n", 1);
		exit(0);
	}
	while (ft_echo_param_checker(node.args[i]) == 1)
		i++;
	while (node.args[i])
	{
		if (node.args[i][0] == '~' && node.args[i][1] == '\0')
		{
			free(node.args[i]);
			node.args[i] = ft_strdup(getenv("HOME"));
		}
		ft_putstr_fd(node.args[i], 1);
		if (node.args[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (ft_echo_param_checker(node.args[1]) == 0)
		ft_putstr_fd("\n", 1);
	exit(0);
}

void	run_exit(t_node node)
{
	int	exit_code;

	printf("exit\n");
	if (node.args[1] && node.args[2])
	{
		printf("tsh: exit: too many arguments\n");
		question_mark_update(ft_strdup("?=1"), -1);
	}
	else
	{
		if (node.args[1])
		{
			if (!ft_number(node.args[1]))
			{
				printf("tsh: exit: %s: numeric argument required\n", \
					node.args[1]);
				exit_code = 255;
			}
			else
				exit_code = ft_atoi(node.args[1]);
		}
		else
			exit_code = g_va->err_number;
		exit(exit_code % 256);
	}
}
