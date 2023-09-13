/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:43:06 by tdemir            #+#    #+#             */
/*   Updated: 2023/09/13 13:18:16 by tdemir           ###   ########.fr       */
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

void	ft_ec(t_token *tokens)
{
	int	i;

	i = -1;
	if (ft_strcmp("echo", tokens[0].value))
	{
		g_va->syn_err = 1;
		while (tokens[1].value[++i])
			printf("%c", tokens[1].value[i]);
		printf("\n");
	}
}

void	ft_spectrum(t_token *tokens)
{
	int	i;

	i = -1;
	while (tokens[++i].value)
	{
		if ((tokens[i].value[0] == '<'
				&& tokens[i].value[1] == '>')
			|| (tokens[i].value[0] == '>'
				|| tokens[i].value[1] == '<'))
		{
			g_va->syn_err = 1;
			printf("Xtsh: syntax error near unexpected token `newline'\n");
			question_mark_update(ft_strdup("?=258"), 258);
		}
	}
}
