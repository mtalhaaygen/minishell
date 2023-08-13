/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:09:03 by maygen            #+#    #+#             */
/*   Updated: 2023/08/09 12:38:32 by tdemir           ###   ########.fr       */
=======
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:09:03 by maygen            #+#    #+#             */
/*   Updated: 2023/08/13 20:41:59 by marvin           ###   ########.fr       */
>>>>>>> master
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



char *ft_dup(char *input, int start, int end)
{
	int		i;
	int		k;
	char	*str;

	k = 0;
	i = start;
	str = malloc(end - start + 1);
	if (!str)
		return (NULL);
	while(i < end && input[i])
	{
		while (input[i] == 34 && gv.flag == 1)
			i++;
		while(input[i] == 39 && gv.flag == 2)
			i++;
		if(i<end)
			str[k] = input[i];
		i++;
		k++;
	}
	////hata buaradadcdasıdslauf0 BEADSfn
	if(!str[k-1])
		str[k-1] = '\0';
	else
		str[k] = '\0';
	return (str);
}

s_token *ft_start(char *input)
{
	s_token *tokens;
	int i;
	int k;
	int start;
	int token_count;

	i = 0;
<<<<<<< HEAD
	k = -1;
=======
	k = 0;
>>>>>>> master
	token_count = ft_token_count(input);
	tokens = ft_calloc(token_count + 1, sizeof(s_token));
	if (!tokens)
		return (NULL);
	while (input[i])
	{
<<<<<<< HEAD
		while (my_isspace(input[i]))
				i++;
		start = i;
		i = ft_find_end(input, i);
		tokens[++k].value = ft_dup(input, start, i);
=======
		tokens[k].quot_flag =0;
		while (my_isspace(input[i]))
				i++;
		if(input[i] == 39 || input[i] == 34 )
			tokens[k].quot_flag = 1;
		start = i;
		i = ft_find_end(input, i);
		tokens[k].value = ft_dup(input, start, i);
		k++;
>>>>>>> master
	}
	tokens[++k].value = NULL;
	
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
	int j;

	
	j = 1;
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
char *ft_rm_last_sp(char *input)
{
	int len;
	char *str;
	len =0;
	while(input[len])
		len++;
	len--;
	while(input[len] == 32)
		len--;
	
	str = ft_calloc(len+1,sizeof(char));
	str[len+1] = '\0';
	while (input[len])
	{
		str[len] = input[len];
		len--;
	}
	return(str);
	
}
<<<<<<< HEAD
=======

/*
dslafidsgldfsg
dfgsdfgşkdfdfs
fidgşdfsigşdfs
*/
char **ft_tmp_tokens(s_token *tokens)
{
	int i;
	i = 0;
	char **tmp;
	tmp = ft_calloc(1,size_of(char *));
	while(tokens[i].value)
	{
		tmp[i] = ft_strdup(tokens[i].value);
		i++;
	}
	tmp[i] = NULL;
	return(tmp);
}
s_token *ft_which_case(s_token *tokens, int i, int j)
{
	char **sp;
	char **tmp_tokens;
	tmp_tokens = ft_tmp_tokens(tokens);
	int tmp;
	tmp = i+1;
	if(tokens[i].value[j-1] && tokens[i].value[j+2])
	{
		sp = ft_split(tokens[i].value, '<');
		tokens[i].value= ft_strdup(sp[0]);
		i++;
		tokens[i].value[0] = '<';
		tokens[i].value[1] = '<';
		tokens[i].value[2] = '\0';
		i++;
		tokens[i].value = ft_strdup(sp[1]);
		i++;
		while(tmp_tokens[tmp])
		{
			tokens[i].value = ft_strdup(tmp_tokens[tmp]);
			i++; 
			tmp++;
		}
		tokens[i] = NULL;
		return (tokens);
	}
	else if(tokens[i].value[j+2])
	{
		sp = ft_split(tokens[i].value, '<');
		tokens[i].value[0] = '<';
		tokens[i].value[1] = '<';
		tokens[i].value[2] = '\0';
		i++;
		tokens[i].value = ft_strdup(sp[0]);
		i++;
		while(tmp_tokens[tmp])
		{
			tokens[i].value = ft_strdup(tmp_tokens[tmp]);
			i++; 
			tmp++;
		}
		tokens[i] = NULL;
		return(tokens);
	}
	else if(tokens[i].value[j-1])
	{
		sp = ft_split(tokens[i].value, '<');
		tokens[i].value = ft_strdup(sp[0]);
		i++;
		
		tokens[i].value[0] = '<';
		tokens[i].value[1] = '<';
		tokens[i].value[2] = '\0';
		i++;
		
		while(tmp_tokens[tmp])
		{
			tokens[i].value = ft_strdup(tmp_tokens[tmp]);
			i++; 
			tmp++;
		}
		tokens[i] = NULL;
		return(tokens);
	}
	
	return(tokens);
}
s_token *ft_sep(s_token *tokens)
{
	int i;
	int j;

	i =0;
	j = 0;
	while(tokens[i].value)
	{
		while(tokens[i].value[j])
		{
			if(tokens[i].value[j] == '<' && tokens[i].value[j+1] == '<' && !tokens[i].quot_flag)
			{
				tokens = ft_which_case(tokens, i, j);
			}
			j++;
		}
		i++;
	}
	return (tokens);
}
/*
dslafidsgldfsg
dfgsdfgşkdfdfs
fidgşdfsigşdfs
*/
>>>>>>> master
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
<<<<<<< HEAD
=======
	tokens = ft_sep(tokens);
>>>>>>> master
	tokens = ft_dollar(tokens);
	tokens = ft_check_sng_que(tokens);
	ft_token_type(tokens);
	
	gv.process_count = ft_pipe_counter(tokens) + 1;
	// printf("%d\n\n", gv.process_count);
	return tokens;
}
