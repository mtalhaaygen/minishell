/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:36:57 by tdemir            #+#    #+#             */
/*   Updated: 2023/09/11 11:46:28 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_double_error(t_token *tokens, int i)
{
	if ((tokens[i].value[0] == '<' 
			|| tokens[i].value[0] == '>') && !tokens[i].quot_flag)
	{
		printf("Xtsh: syntax error near unexpected token `newline'\n");
		question_mark_update("?=258", 258);
	}
	else if (tokens[i].value[0] == '<' && tokens[i].quot_flag)
	{
		printf("<<\n");
	}
	else if (tokens[i].value[0] == '>' && tokens[i].quot_flag)
	{
		printf(">>\n");
	}
}

void	ft_single_error(t_token *tokens, int i)
{
	if ((tokens[i].value[0] == '<' 
			|| tokens[i].value[0] == '>') && !tokens[i].quot_flag)
	{
		printf("Xtsh: syntax error near unexpected token `newline'\n");
		question_mark_update("?=258", 258);
	}
	else if (tokens[i].value[0] == '<' && tokens[i].quot_flag)
	{
		printf("<\n");
	}
	else if (tokens[i].value[0] == '>' && tokens[i].quot_flag)
	{
		printf(">\n");
	}
}

void	ft_error_mesage(t_token *tokens, int i)
{
	if ((tokens[i].value[0] == '<' && !tokens[i].value[1])
		|| (tokens[i].value[0] == '>' && !tokens[i].value[1]))
	{
		g_va->syn_err = 1;
		ft_single_error(tokens, i);
	}
	else if ((tokens[i].value[0] == '>' && tokens[i].value[1] == '>'
			&& !tokens[i].value[2]) || (tokens[i].value[0] == '<'
			&& tokens[i].value[1] == '<' && !tokens[i].value[2]))
	{
		g_va->syn_err = 1;
		ft_double_error(tokens, i);
	}
}

void	ft_pipe_err(void)
{
	g_va->syn_err = 1;
	printf("Xtsh: syntax error near unexpected token `|'\n");
	question_mark_update("?=258", 258);
}

void	ft_print_pipe(t_token *tokens)
{
	int	i;
	int	flag;
	int	flag2;

	flag2 = 0;
	i = -1;
	flag = 1;
	if (tokens[1].value)
	{
		while (tokens[1].value[++i])
		{
			if (tokens[1].value[i] != '|' && tokens[1].value[i]
				!= '<' && tokens[1].value[i] != '>')
				flag = 0;
			if (tokens[1].value[i] == '|')
				flag2 = 1;
		}
		if (flag == 1 && tokens[1].quot_flag && flag2 == 1)
		{
			i = -1;
			if (ft_strcmp("echo", tokens[0].value))
			{
				g_va->syn_err = 1;
				while (tokens[1].value[++i])
					printf("%c", tokens[1].value[i]);
				printf("\n");
			}
		}
		if (flag && !tokens[1].quot_flag && flag2 && !tokens[2].value)
			ft_pipe_err();
	}
	else
		ft_first_pipe(tokens);
}
