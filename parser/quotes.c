/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:37:42 by maygen            #+#    #+#             */
/*   Updated: 2023/09/07 17:05:24 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_char_count(const char *input, int c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	quote_off(const char *input)
{
	int	dq_count;
	int	mq_count;

	mq_count = ft_char_count(input, MQ);
	dq_count = ft_char_count(input, DQ);
	if (dq_count % 2 == 1 || mq_count % 2 == 1)
	{
		printf("quotes count error\n");
		return (1);
	}
	return (0);
}

int	ft_red_pip_count(const char *input)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
			count += 2;
		i++;
	}
	return (count);
}
int	tokencount_forq(const char *input, int i)
{
	int	tmp;

	tmp = input[i];
	while (1)
	{
		i++;
		while (input[i] != tmp && input[i])
			i++;
		i++;
		if (input[i] == '\0' && input[i])
		{
			g_va->counter_num++;
			break ;
		}
		else
		{
			if (my_isspace(input[i]) || input[i] == '\0')
			{
				g_va->counter_num++;
				break ;
			}
			else
				tmp = input[i];
		}
	}
	return (i);
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

int	ft_token_count(const char *input)
{
	int	i;

	i = 0;
	g_va->counter_num = 0;
	while (input[i])
	{
		while (my_isspace(input[i]))
			i++;
		if ((input[i] == DQ || input[i] == MQ) && input[i])
			i = tokencount_forq(input, i);
		else
			i = tokencount_nq(input, i);
	}
	g_va->counter_num += ft_red_pip_count(input);
	return (g_va->counter_num);
}

/*
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
			count++;
*/