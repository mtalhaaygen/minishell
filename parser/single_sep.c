/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_sep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:40:16 by tdemir            #+#    #+#             */
/*   Updated: 2023/09/01 12:15:19 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_val_dup(char val)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	str[0] = val;
	str[1] = '\0';
	return (str);
}

t_token	*ft_r_l_sep_sng(t_token *tokens, int i, char val, char	**tmp_tokens)
{
	char	**sp;
	int		f;
	int		tmp;

	sp = ft_split(tokens[i].value, val);
	i--;
	f = i;
	tmp = i + 1;
	while (tokens[++f].value)
		free (tokens[f].value);
	tokens[++i].value = ft_strdup(sp[0]);
	tokens[++i].value = ft_strdup_dolkey(ft_val_dup (val));
	tokens[++i].value = ft_strdup(sp[1]);
	while (tmp_tokens[++tmp])
		tokens[++i].value = ft_strdup(tmp_tokens[tmp]);
	free (sp[0]);
	free (sp[1]);
	free (sp);
	tokens[++i].value = NULL;
	i = -1;
	while (tmp_tokens[++i])
		free (tmp_tokens[i]);
	free (tmp_tokens);
	return (tokens);
}

t_token	*ft_r_sep_sng(t_token *tokens, int i, char val, char	**tmp_tokens)
{
	char	**sp;
	int		f;
	int		tmp;

	sp = ft_split (tokens[i].value, val);
	i--;
	f = i;
	tmp = i + 1;
	while (tokens[++f].value)
		free (tokens[f].value);
	tokens[++i].value = ft_val_dup(val);
	tokens[++i].value = ft_strdup(sp[0]);
	while (tmp_tokens[++tmp])
		tokens[++i].value = ft_strdup(tmp_tokens[tmp]);
	free (sp[0]);
	free (sp);
	tokens[++i].value = NULL;
	i = -1;
	while (tmp_tokens[++i])
		free (tmp_tokens[i]);
	free (tmp_tokens);
	return (tokens);
}

t_token	*ft_l_sep_sng(t_token *tokens, int i, char val, char	**tmp_tokens)
{
	char	**sp;
	int		f;
	int		tmp;

	sp = ft_split(tokens[i].value, val);
	i--;
	f = i;
	tmp = i + 1;
	while (tokens[++f].value)
		free (tokens[f].value);
	tokens[++i].value = ft_strdup(sp[0]);
	tokens[++i].value = ft_val_dup(val);
	while (tmp_tokens[++tmp])
		tokens[++i].value = ft_strdup(tmp_tokens[tmp]);
	tokens[++i].value = NULL;
	free (sp[0]);
	free (sp);
	i = -1;
	while (tmp_tokens[++i])
		free (tmp_tokens[i]);
	free (tmp_tokens);
	return (tokens);
}

t_token	*ft_single_sep(t_token *tokens, int i, int j, char val)
{
	char	**tmp_tokens;

	tmp_tokens = ft_tmp_tokens(tokens);
	if (j != 0 && tokens[i].value[j + 1])
	{
		tokens = ft_r_l_sep_sng(tokens, i, val, tmp_tokens);
		return (tokens);
	}
	else if (tokens[i].value[j + 1])
	{
		tokens = ft_r_sep_sng(tokens, i, val, tmp_tokens);
		return (tokens);
	}
	else if (j != 0)
	{
		tokens = ft_l_sep_sng(tokens, i, val, tmp_tokens);
		return (tokens);
	}
	free_pp(tmp_tokens);
	return (tokens);
}
