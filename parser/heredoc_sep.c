#include "../minishell.h"

char	**ft_tmp_tokens(s_token *tokens)
{
	char	**tmp_tokens;
	int		i;

	i = 0;
	tmp_tokens = ft_calloc(99, sizeof(char **));
	if (!tmp_tokens)
		return (NULL);
	while (tokens[i].value)
	{
		tmp_tokens[i] = ft_strdup(tokens[i].value);
		i++;
	}
	tmp_tokens[i] = NULL;
	return (tmp_tokens);
}

s_token	*ft_which_heredoc(s_token *tokens, int i, int j)
{
	char	**sp;
	char	**tmp_tokens;
	int		tmp;

	tmp_tokens = ft_tmp_tokens(tokens);
	tmp = i + 1;
	char *here = "<<";

	if(j != 0 && tokens[i].value[j+2])
	{
		sp = ft_split(tokens[i].value, '<');
		int f = i;
		while(tokens[f].value)
		{
			free(tokens[f].value);
			f++;
		}
		tokens[i].value= ft_strdup(sp[0]);
		i++;
		tokens[i].value = ft_strdup(here);
		i++;

		tokens[i].value = ft_strdup(sp[1]);
		i++;

		while(tmp_tokens[tmp])
		{
			tokens[i].value = ft_strdup(tmp_tokens[tmp]);
			i++; 
			tmp++;
		}
		free(sp[0]);
		free(sp[1]);
		free(sp);
		tokens[i].value = NULL;
		i = 0;
		while (tmp_tokens[i])
		{
			free(tmp_tokens[i]);
			i++;
		}
		free(tmp_tokens);
		return (tokens);
	}
	else if(tokens[i].value[j+2])
	{

		sp = ft_split(tokens[i].value, '<');
		int f = i;
		while(tokens[f].value)
		{
			free(tokens[f].value);
			f++;
		}
		printf("debug\n");
		tokens[i].value = ft_strdup(here);
		i++;
		tokens[i].value = ft_strdup(sp[0]);
		i++;
		while(tmp_tokens[tmp])
		{
			tokens[i].value = ft_strdup(tmp_tokens[tmp]);
			i++; 
			tmp++;
		}
		free(sp[0]);
		free(sp);
		tokens[i].value = NULL;
		i = 0;
		while (tmp_tokens[i])
		{
			free(tmp_tokens[i]);
			i++;
		}
		free(tmp_tokens);
		return(tokens);
	}
	else if(j != 0)
	{
		sp = ft_split(tokens[i].value, '<');
		int f = i;
		while(tokens[f].value)
		{
			free(tokens[f].value);
			f++;
		}
		tokens[i].value = ft_strdup(sp[0]);
		i++;
		tokens[i].value = ft_strdup(here);
		i++;
		
		while(tmp_tokens[tmp])
		{
			tokens[i].value = ft_strdup(tmp_tokens[tmp]);
			i++; 
			tmp++;
		}
		tokens[i].value = NULL;
		free(sp[0]);
		free(sp);
		tokens[i].value = NULL;
		i = 0;
		while (tmp_tokens[i])
		{
			free(tmp_tokens[i]);
			i++;
		}
		free(tmp_tokens);
		return(tokens);
	}
	i = 0;
	while (tmp_tokens[i])
	{
		free(tmp_tokens[i]);
		i++;
	}
	free(tmp_tokens);
	return(tokens);
}
s_token *ft_sep(s_token *tokens)
{
	int i;
	int j;
	int len;

	i = 0;
	while (tokens[i].value)
	{
		j = 0;
		len = ft_strlen(tokens[i].value);
		while (j<len)
		{
			if (tokens[i].value[j] == '<' && tokens[i].value[j+1] == '<' && !tokens[i].quot_flag)
			{
				tokens = ft_which_heredoc(tokens, i, j);
				i++;
			}
            else if(tokens[i].value[j] == '<' && !tokens[i].quot_flag)
			{
                tokens = ft_which_reader(tokens, i, j);
				i++;
			}
			else if(tokens[i].value[j] == '>' && tokens[i].value[j+1] == '>' && !tokens[i].quot_flag)
			{
				tokens = ft_which_redirection(tokens, i, j);
				i++;
			}
            else if(tokens[i].value[j] == '>' && !tokens[i].quot_flag)
			{
                tokens = ft_which_append(tokens, i, j);
				i++;
			}
            else if (tokens[i].value[j] == '|' && !tokens[i].quot_flag)
			{
				tokens = ft_which_pipe(tokens, i, j);
				i++;
			}
			j++;
		}
		i++;
	}
	return (tokens);
}