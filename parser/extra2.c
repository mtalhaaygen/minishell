/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:27:09 by tdemir            #+#    #+#             */
/*   Updated: 2023/09/07 16:50:20 by tdemir           ###   ########.fr       */
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
void ft_pipe_error(t_token *tokens, int i)
{
	if(tokens[i].value[0] == '|' && !tokens[i].quot_flag)
	{
		printf("Xtsh: syntax error near unexpected token `|'");
		question_mark_update("?=-258", -258);
	}
	else if(tokens[i].value[0] == '|' && tokens[i].quot_flag)
	{
		printf("|\n");
	}
}

void	ft_double_error(t_token *tokens, int i)
{
	if((tokens[i].value[0] == '<' ||  tokens[i].value[0] == '>') && !tokens[i].quot_flag)
	{
		printf("Xtsh: syntax error near unexpected token `newline'");
		question_mark_update("?=-258", -258);
	}
	else if(tokens[i].value[0] == '<' && tokens[i].quot_flag)
	{
		printf("<<\n");
	}
	else if(tokens[i].value[0] == '>' && tokens[i].quot_flag)
	{
		printf(">>\n");
	}
}

void	ft_single_error(t_token *tokens, int i)
{
	if((tokens[i].value[0] == '<' || tokens[i].value[0] == '>') && !tokens[i].quot_flag)
	{
		printf("Xtsh: syntax error near unexpected token `newline'");
		question_mark_update("?=-258", -258);
	}
	else if(tokens[i].value[0] == '<' && tokens[i].quot_flag)
	{
		printf("<\n");
	}
	else if(tokens[i].value[0] == '>' && tokens[i].quot_flag)
	{
		printf(">\n");
	}
}
void ft_error_mesage(t_token *tokens, int i)
{
	if(tokens[i].value[0] == '|')
		ft_pipe_error(tokens, i);
	else if((tokens[i].value[0] == '>' && tokens[i].value[1] == '>' )|| (tokens[i].value[0] == '<' && tokens[i].value[0] == '<'))
		ft_double_error(tokens, i);
	else if(tokens[i].value[0] == '<' || tokens[i].value[0] == '>')
		ft_single_error(tokens, i);
}
int	ft_eor(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].value)
	{
		if (ft_is_double(tokens, i, 0) || ft_is_mono(tokens, i, 0))
		{
			if (tokens[i].value[2] && ft_is_double(tokens, i, 0))
				return (1);
			if (tokens[i].value[1] && ft_is_mono(tokens, i, 0))
				return (1);
			if (!tokens[i+1].value)
			{
				ft_error_mesage(tokens,i);
				// echo << VS echo |
				
				return (0);
			}
		}
		i++;
	}
	return (1);
}
