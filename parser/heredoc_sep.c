/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_sep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:54:46 by tdemir            #+#    #+#             */
/*   Updated: 2023/09/11 11:41:02 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_tmp_tokens(t_token *tokens)
{
	char	**tmp_tokens;
	int		i;

	i = 0;
	tmp_tokens = ft_calloc(99, sizeof(char **));
	if (!tmp_tokens)
		return (NULL);
	while (tokens[i].value)
	{
		tmp_tokens[i] = ft_strdup(tokens[i].value);
		i++;
	}
	tmp_tokens[i] = NULL;
	return (tmp_tokens);
}

int	ft_is_mono(t_token *tokens, int i, int j)
{
	if (tokens[i].value[j] == '|' && tokens[i].value[j + 1] != '|')
		return (1);
	else if (tokens[i].value[j] == '<' && tokens[i].value[j + 1] != '<')
		return (1);
	else if (tokens[i].value[j] == '>' && tokens[i].value[j + 1] != '>')
		return (1);
	return (0);
}

int	ft_is_double(t_token *tokens, int i, int j)
{
	if (tokens[i].value[j] == '>' && tokens[i].value[j + 1] == '>')
		return (1);
	if (tokens[i].value[j] == '<' && tokens[i].value[j + 1] == '<')
		return (1);
	return (0);
}

t_token	*ft_sep(t_token *tokens)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (tokens[i].value)
	{
		j = 0;
		len = ft_strlen(tokens[i].value);
		while (j < len)
		{
			if (ft_is_double(tokens, i, j) && (!tokens[i].quot_flag))
			{
				tokens = ft_double_sep(tokens, i, j, tokens[i].value[j]);
				i++;
			}
			else if (ft_is_mono(tokens, i, j) && (!tokens[i].quot_flag))
			{
				tokens = ft_single_sep(tokens, i, j, tokens[i].value[j]);
				i++;
			}
			j++;
		}
		i++;
	}
	return (tokens);
}
