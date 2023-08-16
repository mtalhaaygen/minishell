#include "../minishell.h"

s_token *ft_which_pipe(s_token *tokens, int i, int j)
{
	int		tmp;
	char	**sp;
	char	**tmp_tokens;

	tmp = i + 1;
	tmp_tokens = ft_tmp_tokens(tokens);
	char *here = "|";


	if (j != 0 && tokens[i].value[j + 1])
	{

		sp = ft_split(tokens[i].value, '|');
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
	else if(tokens[i].value[j+1])
	{

		sp = ft_split(tokens[i].value, '|');
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
		sp = ft_split(tokens[i].value, '|');
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