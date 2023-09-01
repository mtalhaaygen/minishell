/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_sep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 11:32:34 by tdemir            #+#    #+#             */
/*   Updated: 2023/09/01 12:15:03 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_full_here(char val)
{
	char	*here;

	here = ft_calloc(3, sizeof(char));
	here[0] = val;
	here[1] = val;
	here[2] = '\0';
	return (here);
}

t_token	*ft_r_l_sep(t_token *tokens, int i, char val, char	**tmp_tokens)
{
	int		tmp;
	char	**sp;
	int		f;
	char	*here;

	here = ft_full_here(val);
	sp = ft_split (tokens[i].value, val);
	i = i -1;
	f = i;
	tmp = i + 1;
	while (tokens[++f].value)
		free (tokens[f].value);
	tokens[++i].value = ft_strdup (sp[0]);
	tokens[++i].value = ft_strdup_dolkey (here);
	tokens[++i].value = ft_strdup (sp[1]);
	while (tmp_tokens[++tmp])
		tokens[++i].value = ft_strdup (tmp_tokens[tmp]);
	free_pp (sp);
	tokens[++i].value = NULL;
	i = -1;
	while (tmp_tokens[++i])
		free (tmp_tokens[i]);
	free (tmp_tokens);
	return (tokens);
}

t_token	*ft_r_sep(t_token *tokens, int i, char val, char	**tmp_tokens)
{
	int		tmp;
	char	**sp;
	int		f;
	char	*here;

	here = ft_full_here (val);
	sp = ft_split (tokens[i].value, val);
	i = i -1;
	f = i;
	tmp = i + 1;
	while (tokens[++f].value)
		free (tokens[f].value);
	tokens[++i].value = ft_strdup_dolkey (here);
	tokens[++i].value = ft_strdup (sp[0]);
	while (tmp_tokens[++tmp])
		tokens[++i].value = ft_strdup (tmp_tokens[tmp]);
	free (sp[0]);
	free (sp);
	tokens[++i].value = NULL;
	i = -1;
	while (tmp_tokens[++i])
		free(tmp_tokens[i]);
	free (tmp_tokens);
	return (tokens);
}

t_token	*ft_l_sep(t_token *tokens, int i, char val, char	**tmp_tokens)
{
	int		tmp;
	char	**sp;
	int		f;
	char	*here;

	here = ft_full_here(val);
	sp = ft_split (tokens[i].value, val);
	i = i - 1;
	f = i;
	tmp = i + 1;
	while (tokens[++f].value)
		free (tokens[f].value);
	tokens[++i].value = ft_strdup (sp[0]);
	tokens[++i].value = ft_strdup_dolkey (here);
	while (tmp_tokens[++tmp])
		tokens[++i].value = ft_strdup (tmp_tokens[tmp]);
	tokens[++i].value = NULL;
	free (sp[0]);
	free (sp);
	i = -1;
	while (tmp_tokens[++i])
		free (tmp_tokens[i]);
	free (tmp_tokens);
	return (tokens);
}

t_token	*ft_double_sep(t_token *tokens, int i, int j, char val)
{
	char	**tmp_tokens;

	tmp_tokens = ft_tmp_tokens (tokens);
	if (j != 0 && tokens[i].value[j + 2])
	{
		tokens = ft_r_l_sep (tokens, i, val, tmp_tokens);
		return (tokens);
	}
	else if (tokens[i].value[j + 2])
	{
		tokens = ft_r_sep (tokens, i, val, tmp_tokens);
		return (tokens);
	}
	else if (j != 0)
	{
		tokens = ft_l_sep (tokens, i, val, tmp_tokens);
		return (tokens);
	}
	i = -1;
	while (tmp_tokens[++i])
		free (tmp_tokens[i]);
	free (tmp_tokens);
	return (tokens);
}
