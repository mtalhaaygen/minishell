/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:37:42 by maygen            #+#    #+#             */
/*   Updated: 2023/08/27 19:49:09 by tdemir           ###   ########.fr       */
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
int	ft_token_count(const char *input)
{
	int	i;
	int	tmp;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		while (my_isspace(input[i]))
			i++;
		if ((input[i] == DQ || input[i] == MQ) && input[i])
		{
			tmp = input[i];
			while (1)
			{
				i++;
				while (input[i] != tmp && input[i])
					i++;
				i++;
				if (input[i] == '\0' && input[i])
				{
					count++;
					break ;
				}
				else
				{
					if (my_isspace(input[i]) || input[i] == '\0')
					{
						count++;
						break ;
					}
					else
						tmp = input[i];
				}
			}
		}
		else
		{
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
		}
	}
	count += ft_red_pip_count(input);
	return (count);
}
