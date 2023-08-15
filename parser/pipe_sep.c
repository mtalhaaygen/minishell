#include "../minishell.h"

int	ft_is_write(char c)
{
	if (c < 127 && c > 32)
		return (0);
	return (1);
}
s_token *ft_which_pipe(s_token *tokens, int i, int j)
{
	int		tmp;
	char	**sp;
	char	**tmp_tokens;

	tmp = i + 1;
	tmp_tokens = ft_tmp_tokens(tokens);
	char *here = "|";


	if (!ft_is_write(tokens[i].value[j - 1]) && tokens[i].value[j + 1])
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
	else if(!ft_is_write(tokens[i].value[j - 1]))
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