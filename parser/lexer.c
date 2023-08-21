/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:09:03 by maygen            #+#    #+#             */
/*   Updated: 2023/08/21 12:10:43 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_quotes(int i,const char *str, char del)
{
	int	j;

	j = 0;
	if (str[i + j] == del)
	{
		j++;
		while (str[i+j] != del && str[i + j]  )
		{
			j++;
		}
		
	}
	return (j);
}

int ft_flag(const char *input, int start)
{
	if (input[start] == 34)
		return(1);
	return (0);
}

int	ft_find_end(const char *input, int i)
{
	while (input[i])
	{
		if(input[i] == 34 || input[i] == 39)
			gv.flag = ft_flag(input, i);
		i += handle_quotes(i , input, 34);
		i += handle_quotes(i , input, 39);
		if (my_isspace(input[i]))
			break ;
		else
			i++;
	}
	return (i);
}

void ft_dup(s_token *tokens, char *input, int start, int end, int iter)
{
	int		i;
	int		k;
	char	*str;

	k = 0;
	i = start;
	str = malloc(end - start + 1);
	while (i < end && input[i])
	{
		while (input[i] == 34 && gv.flag == 1)
			i++;
		while (input[i] == 39 && gv.flag == 0)
			i++;
		if (i < end)
		{
			str[k] = input[i];
			k++;
		}
		i++;
	}
	str[k] = '\0';
	tokens[iter].value = ft_strdup(str);
	free(str);
}

s_token	*ft_start(char *input)
{
	s_token *tokens;
	int i;
	int k;
	int start;
	int token_count;

	i = 0;
	k = 0;
	token_count = ft_token_count(input);
	tokens = ft_calloc(token_count + 1, sizeof(s_token));
	if (!tokens)
		return (NULL);
	while (input[i])
	{
		tokens[k].quot_flag = 0;
		while (my_isspace(input[i]))
				i++;
		if(input[i] == 39 || input[i] == 34)
			tokens[k].quot_flag = 1;
		start = i;
		i = ft_find_end(input, i);
		ft_dup(tokens, input,start, i, k);
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
s_token *ft_check_sng_que(s_token *tokens)
{
	int i;
	// int j;

	
	// j = 1;
	i = 0;
	while(tokens[i].value)
	{
		if(tokens[i].value[0] == 39)
		{
			tokens[i].value = ft_strtrim(tokens[i].value,"'");
		}
		i++;
	}
	return (tokens);
}

char	*ft_rm_last_sp(char *input)
{
	int		len;
	char	*str;

	len = ft_strlen(input);
	len--;
	while (input[len] == 32)
		len--;
	str = ft_calloc(len + 2, sizeof(char));
	str[len + 1] = '\0';
	while (len >= 0)
	{
		str[len] = input[len];
		len--;
	}
	return (str);
}

s_token *ft_tokens(char *input)
{
	s_token *tokens;
	
	input = ft_rm_last_sp(input);
	if (quote_off(input))
	{
		tokens = malloc(sizeof(s_token) * 1);
		tokens[0].value = NULL;	
		return (tokens);
	}
	tokens = ft_start(input);
	free(input);
	tokens = ft_sep(tokens);
	tokens = ft_dollar(tokens);
	//tokens = ft_check_sng_que(tokens);
	ft_token_type(tokens);	
	gv.process_count = ft_pipe_counter(tokens) + 1;
	return tokens;
}