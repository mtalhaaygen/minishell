#include "../minishell.h"

char	**ft_tmp_tokens(s_token *tokens)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_calloc(99, sizeof(char **));
	if (!tmp)
		return (NULL);
	while (tokens[i].value)
	{
		tmp[i] = ft_strdup(tokens[i].value);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
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
		tokens[i].value = NULL;
		return (tokens);
	}
	else if(tokens[i].value[j+2])
	{

		sp = ft_split(tokens[i].value, '<');
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
		tokens[i].value = NULL;
		return(tokens);
	}
	else if(j != 0)
	{
		sp = ft_split(tokens[i].value, '<');
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
		return(tokens);
	}
	
	return(tokens);
}
s_token *ft_sep(s_token *tokens)
{
	int i;
	int j;

	i = 0;
	while (tokens[i].value)
	{
		j = 0;
		while (tokens[i].value[j])
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