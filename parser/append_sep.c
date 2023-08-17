#include "../minishell.h"

s_token *ft_which_append(s_token *tokens, int i, int j)
{
	char	**sp;
	char	**tmp_tokens;
	int		tmp;

	tmp_tokens = ft_tmp_tokens(tokens);
	tmp = i + 1;
	char *here = ">";

	if(j != 0 && tokens[i].value[j+2])
	{
		sp = ft_split(tokens[i].value, '>');
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

		sp = ft_split(tokens[i].value, '>');
		int f = i;
		while(tokens[f].value)
		{
			free(tokens[f].value);
			f++;
		}
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
		sp = ft_split(tokens[i].value, '>');
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