/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:09:03 by maygen            #+#    #+#             */
/*   Updated: 2023/09/15 17:01:50 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_find_end(const char *input, int i)
{
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
			g_va->flag = ft_flag(input, i);
		i += handle_quotes(i, input, 34);
		i += handle_quotes(i, input, 39);
		if (my_isspace(input[i]))
			break ;
		else
			i++;
	}
	return (i);
}

void	ft_dup(t_token *token, char *input, int start, int end)
{
	int		i;
	int		k;
	char	*str;

	k = 0;
	i = start;
	str = malloc(end - start + 1);
	while (i < end && input[i])
	{
		while (input[i] == 34 && g_va->flag == 1)
			i++;
		while (input[i] == 39 && g_va->flag == 0)
			i++;
		if (i < end)
		{
			str[k] = input[i];
			k++;
		}
		i++;
	}
	str[k] = '\0';
	token->value = ft_strdup(str);
	free(str);
}

t_token	*ft_start(char *input)
{
	t_token		*tokens;
	int			i;
	int			k;
	int			start;
	int			token_count;

	i = 0;
	k = 0;
	token_count = ft_token_count(input);
	tokens = ft_calloc(token_count + 3, sizeof(t_token));
	while (input[i])
	{
		tokens[k].fq = 0;
		while (my_isspace(input[i]))
			i++;
		tokens[k].quot_flag = ft_tokens_quot_flag(input, i);
		if (input[i] == 39)
			tokens[k].fq = 1;
		start = i;
		i = ft_find_end(input, i);
		ft_dup (&tokens[k], input, start, i);
		k++;
	}
	tokens[k].value = NULL;
	return (tokens);
}

char	*ft_rm_last_sp(char *input)
{
	int		len;
	char	*str;

	len = ft_strlen(input);
	len--;
	while (input[len] == 32)
		len--;
	str = ft_calloc(len + 2, sizeof(char));
	str[len + 1] = '\0';
	while (len >= 0)
	{
		str[len] = input[len];
		len--;
	}
	return (str);
}

t_token	*ft_tokens(char *input)
{
	t_token	*tokens;

	input = ft_rm_last_sp(input);
	if (quote_off(input))
	{
		tokens = malloc(sizeof(t_token) * 1);
		tokens[0].value = NULL;
		free (input);
		return (tokens);
	}
	tokens = ft_start(input);
	free (input);
	ft_eor(tokens, -1);
	if (!g_va->syn_err && ft_pure(tokens))
		tokens = ft_sep(tokens);
	tokens = ft_dollar(tokens);
	ft_token_type (tokens);
	g_va->process_count = ft_pipe_counter(tokens) + 1;
	return (tokens);
}
