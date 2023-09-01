/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:55:10 by maygen            #+#    #+#             */
/*   Updated: 2023/09/01 12:48:16 by maygen           ###   ########.fr       */
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

//yalnızca stdinden girdi alıp stdouta yada yönlendirme ile
// dosyaya çıktı veren bir komut
void	run_echo(Node node)
{
	int	i;

	i = 1;
	if (node.args[i] == NULL)
	{
		ft_putstr_fd("\n", 1);
		return ;
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

void	run_exit(Node node)
{
	int	exit_code;

	printf("exit\n");
	if (node.args[1] && node.args[2])
		printf("tsh: exit: too many arguments\n");
	else
	{
		if (node.args[1])
		{
			if (!ft_number(node.args[1]))
			{
				printf("numbr değil\n");
				exit_code = 255;
			}
			else
				exit_code = ft_atoi(node.args[1]);
		}
		else
			exit_code = 0;
		printf("exitcode:*%d*\n", exit_code);
		exit(exit_code % 256);
	}
}
