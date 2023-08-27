/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:53:43 by tdemir            #+#    #+#             */
/*   Updated: 2023/08/27 15:49:41 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_token_type(s_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].value)
	{
		if (tokens[i].value[0] == '|')
			tokens[i].type = TOKEN_PIPE;
		else if (tokens[i].value[0] == '<' && tokens[i].value[1] == '<')
			tokens[i].type = TOKEN_O_O;
		else if (tokens[i].value[0] == '>' && tokens[i].value[1] == '>')
			tokens[i].type = TOKEN_I_I;
		else if (tokens[i].value[0] == '>')
			tokens[i].type = TOKEN_I;
		else if (tokens[i].value[0] == '<')
			tokens[i].type = TOKEN_O;
		else if (tokens[i].value[0] == '\0')
			tokens[i].type = TOKEN_EOF;
		else
			tokens[i].type = TOKEN_WORD;
		i++;
	}
}

int	handle_quotes(int i, const char *str, char del)
{
	int	j;

	j = 0;
	if (str[i + j] == del)
	{
		j++;
		while (str[i + j] != del && str[i + j])
		{
			j++;
		}
	}
	return (j);
}

int	ft_flag(const char *input, int start)
{
	if (input[start] == 34)
		return (1);
	return (0);
}

s_token	*dollar_plass(s_token *tokens, int i, int j)
{
	char	*dolkey;
	char	*dolval;

	dolkey = ft_strdup_dolkey(ft_dolkey(tokens, i, j));
	if (ft_dolval(dolkey))
	{
		dolval = ft_strdup(ft_dolval(dolkey));
		ft_change_token (dolval, tokens, i, j);
		free(dolval);
	}
	else
		ft_wod (tokens, i);
	free (dolkey);
	return (tokens);
}

int	ft_tokens_quot_flag(char *input, int i)
{
	if (input[i] == 39 || input[i] == 34)
		return (1);
	return (0);
}
