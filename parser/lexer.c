/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:09:03 by maygen            #+#    #+#             */
/*   Updated: 2023/08/03 16:54:10 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_find_end(const char *input, int i)
{
	while (input[i])
	{
		i += handle_quotes(i , input, 34);
		i += handle_quotes(i , input, 39);
		if (my_isspace(input[i]))
			break ;
		else
			i++;
	}
	return (i);
}

int	handle_quotes(int i, char *str, char del)
{
	int	j;

	j = 0;
	if (str[i + j] == del)
	{
		j++;
		while (str[i + j] != del && str[i + j])
			j++;
		j++;
	}
	return (j);
}

int ft_flag(char *input, int i)
{

	if(input[i-1] == 34)
		return(1);
	return (0);
}

char *ft_dup(char *input, int start, int end)
{
	int i;
	i = start;
	char *str;
	int k;
	int flag;
	str = malloc(end-start+1);
	
	k = 0;
	flag = ft_flag(input, start);
	while(i < end)
	{
		while (input[i] == 34 && flag == 1)
			i++;
		while(input[i] == 39 && flag == 0)
			i++;
		str[k] = input[i];
		i++;
		k++;
	}
	return (str);
}

s_token *ft_start(char *input)
{
	s_token *tokens;
	int i;
	int k;
	int start;
	int end;
	int token_count;

	i = 0;
	k = -1;
	token_count = ft_token_count(input);
	tokens = ft_calloc(token_count, sizeof(s_token));
	if (!tokens)
		return (NULL);
	while (input[i])
	{
		while (my_isspace(input[i]))
				i++;
		start = i;
		if(input[i] == 34 || input[i] == 39)
				start++;	
		end = ft_find_end(input, i)
		tokens[++k].value = ft_dup(input,start,end);
		printf("%s\n", tokens[k].value);
	}
	tokens[k].value = NULL;
	return (tokens);
}

void	ft_token_type(s_token *tokens)
{
	int i;

	i = 0;
	while (tokens[i].value)
	{
		if(tokens[i].value[0] == '|')
			tokens[i].type = TOKEN_PIPE;
		else if(tokens[i].value[0] == '<' && tokens[i].value[1] == '<')
			tokens[i].type = TOKEN_O_O;
		else if(tokens[i].value[0] == '>' && tokens[i].value[1] == '>')
			tokens[i].type = TOKEN_I_I;
		else if(tokens[i].value[0] == '>')
			tokens[i].type = TOKEN_I;
		else if(tokens[i].value[0] == '<')
			tokens[i].type = TOKEN_O;
		else if(tokens[i].value[0] == '\0')
			tokens[i].type = TOKEN_EOF;
		else
			tokens[i].type = TOKEN_WORD;
		i++;
	}
}

s_token *ft_tokens(char *input)
{
	s_token *tokens;

	tokens = ft_start(input);
	ft_token_type(tokens);
	
	gv.process_count = ft_pipe_counter(tokens) + 1;
	// printf("%d\n\n", gv.process_count);
	return tokens;
}
