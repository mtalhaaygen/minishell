/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:06:36 by maygen            #+#    #+#             */
/*   Updated: 2023/09/12 14:15:28 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pipe_counter(t_token *tokens)
{
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == TOKEN_PIPE)
			len++;
		i++;
	}
	return (len);
}

int	ft_count_arg(t_token *tokens, int i)
{
	int	len;

	len = 0;
	while (tokens[i].type != TOKEN_PIPE && tokens[i].value)
	{
		len++;
		i++;
	}
	return (len);
}

t_node	ft_creat_node(t_token *tokens, int i)
{
	t_node	node;
	int		j;
	int		count;

	count = 0;
	node.infile = ft_calloc(1, sizeof(t_file));
	node.outfile = ft_calloc(1, sizeof(t_file));
	node.args = ft_calloc(sizeof(char *), ft_count_arg(tokens, i) + 1);
	j = 0;
	while (tokens[i].type != TOKEN_PIPE && tokens[i].value)
	{
		node.args[j] = ft_strdup(tokens[i].value);
		if (tokens[i].type == TOKEN_I)
			ft_i(node, i, tokens);
		if (tokens[i].type == TOKEN_I_I)
			ft_i_i(node, i, tokens);
		if (tokens[i].type == TOKEN_O)
			ft_o(node, i, tokens);
		i++;
		j++;
		count++;
	}
	node.args[j] = NULL;
	node.arg_count = count;
	return (node);
}

t_node	*ft_parser(t_token *tokens)
{
	t_node	*nodes;
	int		i;
	int		j;
	int		pipe_len;

	pipe_len = g_va->process_count;
	nodes = malloc (sizeof(t_node) * (pipe_len + 1));
	i = 0;
	j = 0;
	nodes[j] = ft_creat_node (tokens, i);
	while (tokens[i].value)
	{
		if (tokens[i].type == TOKEN_PIPE)
		{
			j++;
			nodes[j] = ft_creat_node(tokens, i + 1);
		}
		i++;
	}
	return (nodes);
}
