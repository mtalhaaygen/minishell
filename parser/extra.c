/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:53:43 by tdemir            #+#    #+#             */
/*   Updated: 2023/08/27 13:53:51 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
