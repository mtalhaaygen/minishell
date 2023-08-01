/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:09:03 by maygen            #+#    #+#             */
/*   Updated: 2023/08/01 13:22:19 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

s_token *ft_start(char *input)
{
	s_token *tokens;
	int i;
	// int j;
	int k;
	int start;
	int end;

	i = 0;
	k = 0;
	tokens = malloc(sizeof(s_token) * 99); // inputu split yada benzeri bir fonk. ile ayırıp tokens sayısı kadar yer açabilirsin
	if (!tokens)
		return (NULL);
	while (input[i])
	{
		// j = 0;
		while (my_isspace(input[i]))
			i++;
		start = i;
		while (!my_isspace(input[i]) && input[i] != '\0')
			i++;
		end = i;
		if (input[i - 1] && !my_isspace(input[i - 1]))
			tokens[k].value = ft_substr(input, start, end-start);
		k++;
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
