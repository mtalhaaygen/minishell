/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:43:06 by tdemir            #+#    #+#             */
/*   Updated: 2023/09/11 11:49:09 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pure(t_token *tokens)
{
	int	i;
	int	j;

	i = 0;
	while (tokens[i].value)
	{
		j = 0;
		while (tokens[i].value[j])
		{
			if (tokens[i].value[j] != '|' && tokens[j].value[j] \
				!= '<' && tokens[i].value[j] != '>')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	tokencount_nq(const char *input, int i)
{
	int	tmp;

	while ((!my_isspace(input[i])) && input[i])
	{
		if (input[i] == DQ || input[i] == MQ)
		{
			tmp = input[i];
			i++;
			while (input[i] != tmp && input[i])
				i++;
		}
		else
			i++;
	}
	g_va->counter_num++;
	return (i);
}
