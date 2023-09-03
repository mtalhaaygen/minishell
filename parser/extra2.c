/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:27:09 by tdemir            #+#    #+#             */
/*   Updated: 2023/09/03 17:06:06 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_i(t_node node, int i, t_token *tokens)
{
	node.outfile->type = TOKEN_I;
	node.outfile->name = ft_strdup (tokens[i + 1].value);
}

void	ft_i_i(t_node node, int i, t_token *tokens)
{
	node.outfile->type = TOKEN_I_I;
	node.outfile->name = ft_strdup (tokens[i + 1].value);
}

void	ft_o(t_node node, int i, t_token *tokens)
{
	node.infile->type = TOKEN_O;
	node.infile->name = ft_strdup (tokens[i + 1].value);
}
