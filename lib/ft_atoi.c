/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:05:27 by maygen            #+#    #+#             */
/*   Updated: 2023/09/10 19:44:38 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		neg;
	long	res;

	i = 0;
	neg = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48) * neg;
		i++;
	}
	return (res);
}

void	ft_i_i(t_node node, int i, t_token *tokens)
{
	node.outfile->type = TOKEN_I_I;
	node.outfile->name = ft_strdup (tokens[i + 1].value);
}

void	ft_i(t_node node, int i, t_token *tokens)
{
	node.outfile->type = TOKEN_I;
	node.outfile->name = ft_strdup (tokens[i + 1].value);
}
