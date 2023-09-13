/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:27:09 by tdemir            #+#    #+#             */
/*   Updated: 2023/09/13 13:16:21 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_first_pipe(t_token *tokens)
{
	int	i;
	int	flag;

	flag = 1;
	i = 0;
	if (tokens[0].value)
	{
		while (tokens[0].value[i])
		{
			if (tokens[0].value[i] != '|')
				flag = 0;
			i++;
		}
	}
	if (flag && !tokens[2].value && tokens[0].value)
		ft_pipe_err();
}

int	ft_pure_too(t_token *tokens, int i)
{
	int	j;
	int	len;

	len = ft_strlen(tokens[i].value);
	j = 0;
	while (j < len)
	{
		if (tokens[i].value[j] != '|'
			&& tokens[i].value[j] != '<' && tokens[i].value[j] != '>')
		{
			return (1);
		}
		j++;
	}
	return (0);
}

int	ft_pure_the(t_token *tokens, int i)
{
	int	j;
	int	len;

	len = ft_strlen(tokens[i].value);
	j = 0;
	while (j < len)
	{
		if (tokens[i].value[j] != '<' && tokens[i].value[j] != '>')
		{
			return (1);
		}
		j++;
	}
	return (0);
}

void	ft_em(void)
{
	g_va->syn_err = 1;
	printf("Xtsh: syntax error near unexpected token `newline'\n");
	question_mark_update(ft_strdup("?=258"), 258);
}

int	ft_eor(t_token *tokens, int i)
{
	ft_print_pipe(tokens);
	ft_spectrum(tokens);
	while (tokens[++i].value)
	{
		if (ft_is_double(tokens, i, 0)
			|| ft_is_mono(tokens, i, 0) || (ft_pure(tokens) == 0))
		{
			if (!ft_pure_the(tokens, i)
				&& tokens[i].value[2] && !tokens[i].quot_flag)
				ft_em();
			if (tokens[i].value[2]
				&& ft_is_double(tokens, i, 0) && ft_pure_too(tokens, i))
				return (1);
			if (tokens[i].value[1]
				&& ft_is_mono(tokens, i, 0) && ft_pure_too(tokens, i))
				return (1);
			if (!tokens[i + 1].value)
			{
				ft_error_mesage(tokens, i);
				return (0);
			}
		}
	}
	return (1);
}
