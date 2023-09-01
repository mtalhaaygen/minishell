/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:06:36 by maygen            #+#    #+#             */
/*   Updated: 2023/09/01 12:07:27 by maygen           ###   ########.fr       */
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

Node	ft_creat_node(t_token *tokens, int i)
{
	Node	node;
	int		j;

	node.infile = ft_calloc(1, sizeof(t_file));
	node.outfile = ft_calloc(1, sizeof(t_file));
	node.args = ft_calloc(sizeof(char *), ft_count_arg(tokens, i) + 1); 
	if (!node.args)
		return (node); 
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
	}
	node.args[j] = NULL;
	node.arg_count = i;
	return (node);
}

Node	*ft_parser(t_token *tokens)
{
	Node	*nodes;
	int		i;
	int		j;
	int		pipe_len;

	pipe_len = g_va->process_count;
	nodes = malloc (sizeof(Node) * (pipe_len + 1));
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
