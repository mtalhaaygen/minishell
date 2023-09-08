/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:27:09 by tdemir            #+#    #+#             */
/*   Updated: 2023/09/08 16:30:54 by tdemir           ###   ########.fr       */
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


void	ft_double_error(t_token *tokens, int i)
{
	if((tokens[i].value[0] == '<' ||  tokens[i].value[0] == '>') && !tokens[i].quot_flag)
	{
		printf("Xtsh: syntax error near unexpected token `newline'\n");
		question_mark_update("?=258", 258);
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
		printf("Xtsh: syntax error near unexpected token `newline'\n");
		question_mark_update("?=258", 258);

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
	if ((tokens[i].value[0] == '<'  && !tokens[i].value[1] )|| (tokens[i].value[0] == '>' && !tokens[i].value[1] ))
	{
		g_va->syn_err = 1;
		ft_single_error(tokens, i);
	}
	else if ((tokens[i].value[0] == '>' && tokens[i].value[1] == '>' && !tokens[i].value[2]) || (tokens[i].value[0] == '<' && tokens[i].value[1] == '<' && !tokens[i].value[2]))
	{
		g_va->syn_err = 1;
		ft_double_error(tokens, i);
	}
}

void ft_pipe_err()
{
	g_va->syn_err = 1;
	printf("Xtsh: syntax error near unexpected token `|'\n");
	question_mark_update("?=258", 258);
}

void ft_first_pipe(t_token *tokens)
{
	int i;
	int flag;
	flag = 1;
	i = 0;
	while(tokens[0].value[i])
	{
		if(tokens[0].value[i] != '|')
			flag = 0;
		i++;
	}
	
	if (flag && !tokens[2].value)
		ft_pipe_err();
}
void ft_print_pipe(t_token *tokens)
{
	int	i;
	int	flag;
	int flag2;
	
	flag2 = 0;
	i = -1;
	flag = 1;
	if (tokens[1].value)
	{
		while (tokens[1].value[++i])
		{
			if (tokens[1].value[i] != '|' && tokens[1].value[i] != '<' && tokens[1].value[i] != '>')
				flag = 0;
			if(tokens[1].value[i] == '|')
				flag2 = 1;
		}
		if (flag == 1 && tokens[1].quot_flag && flag2 == 1)
		{
			i = -1;
			if(ft_strcmp("echo", tokens[0].value))
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
	{

		ft_first_pipe(tokens);
	}

}

int ft_pure_too(t_token *tokens, int i)
{
	int j;
	int len;

	len = ft_strlen(tokens[i].value);
	j = 0;
	while (j < len)
	{
		if (tokens[i].value[j] != '|' && tokens[i].value[j] != '<' && tokens[i].value[j] != '>')
		{
			return (1);
		}
		j++;
	}

	return (0);
}

int ft_pure_the(t_token *tokens, int i)
{
	int j;
	int len;

	len = ft_strlen(tokens[i].value);
	j = 0;
	while (j < len)
	{
		if (tokens[i].value[j] != '<' && tokens[i].value[j] != '>')
		{
			return (1);
		}
		j++;
	}

	return (0);
}

int	ft_eor(t_token *tokens)
{
	int	i;

	i = 0;
	ft_print_pipe(tokens);
	
	while (tokens[i].value)
	{
		if (ft_is_double(tokens, i, 0) || ft_is_mono(tokens, i, 0) || (ft_pure(tokens) == 0))
		{
			if(!ft_pure_the(tokens, i) && tokens[i].value[2] && !tokens[i].quot_flag)
			{
				g_va->syn_err = 1;
				printf("Xtsh: syntax error near unexpected token `newline'\n");
				question_mark_update("?=258", 258);
			}
			if (tokens[i].value[2] && ft_is_double(tokens, i, 0) && ft_pure_too(tokens,i))
				return (1);
			if (tokens[i].value[1] && ft_is_mono(tokens, i, 0) && ft_pure_too(tokens,i))
				return (1);
			if (!tokens[i+1].value)
			{
				ft_error_mesage(tokens,i);
				return (0);
			}
			
		}
		i++;
	}
	return (1);
}
