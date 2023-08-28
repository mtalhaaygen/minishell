/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:21:27 by maygen            #+#    #+#             */
/*   Updated: 2023/08/28 14:49:27 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	contain_i(char **commands)
{
	int	index;

	index = 0;
	while (commands[index])
	{
		if (commands[index][0] == '>')
			if (commands[index][1] == '\0')
				return (index);
		index++;
	}
	return (0);
}

int	contain_o(char **commands)
{
	int	index;

	index = 0;
	while (commands[index])
	{
		if (commands[index][0] == '<')
			if (commands[index][1] == '\0')
				return (index);
		index++;
	}
	return (0);
}

int	contain_ii(char **commands)
{
	int	index;

	index = 0;
	while (commands[index])
	{
		if (commands[index][0] == '>')
			if (commands[index][1] == '>')
				return (index);
		index++;
	}
	return (0);
}
