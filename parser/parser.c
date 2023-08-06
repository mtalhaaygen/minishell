/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:06:36 by maygen            #+#    #+#             */
/*   Updated: 2023/08/06 15:02:18 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_pipe_counter(s_token *tokens)
{
	int len;
	int i;

	i = 0;
	len = 0;
	while(tokens[i].value)
	{
		if(tokens[i].type == TOKEN_PIPE)
			len++;
		i++;
	}
	return (len);
}

int ft_count_arg(s_token *tokens, int i)
{
	int len;
	
	len = 0;
	while(tokens[i].type != TOKEN_PIPE && tokens[i].value)
	{
		len++;
		i++;
	}
	return (len);
}

Node ft_creat_node(s_token *tokens, int i)
{
	Node node;
	int j;

	node.infile = NULL;
	node.outfile = NULL;
	node.args = ft_calloc(sizeof(char *), ft_count_arg(tokens, i) + 1); // + 1 null için
	if (!node.args)
		return (node); // bu return değeri değişebilir
	j = 0;
	while(tokens[i].type != TOKEN_PIPE && tokens[i].value)
	{
		node.args[j] = ft_strdup(tokens[i].value);
		if(tokens[i].type == TOKEN_I)
		{
			node.infile->type = TOKEN_I;
			node.infile->name = ft_strdup("in");
		}
		if(tokens[i].type == TOKEN_I_I)
		{
			node.infile->type = TOKEN_I_I;
			node.infile->name = ft_strdup("double_in");
		}
		if(tokens[i].type == TOKEN_O)
		{
			node.infile->type = TOKEN_O;
			node.infile->name = ft_strdup("out");
		}
		if(tokens[i].type == TOKEN_O_O)
		{
			node.infile->type = TOKEN_O_O;
			node.infile->name = ft_strdup("double_out");
		}
		i++;
		j++;
	}
	node.args[j] = NULL;
	node.arg_count = i;
	return (node);
}

Node	*ft_parser(s_token *tokens)
{
	Node *nodes;
	int i;
	int j;
	int pipe_len;

	pipe_len = gv.process_count;
	nodes = malloc(sizeof(Node) * (pipe_len + 1));
	if (!nodes)
		return (NULL);
	i = 0;
	j = 0;
	nodes[j] = ft_creat_node(tokens, i);
	while(tokens[i].value)
	{
		//printf("*%s*\n",tokens[i].value);
		if(tokens[i].type == TOKEN_PIPE)
		{
			j++;
			nodes[j] = ft_creat_node(tokens,i+1);
		}
		i++;
	}
	return (nodes);
}