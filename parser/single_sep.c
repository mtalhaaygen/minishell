#include "../minishell.h"

s_token *ft_r_l_sep_sng(s_token *tokens, int i, char val,char	**tmp_tokens, int tmp)
{
		char	**sp;
		sp = ft_split(tokens[i].value, val);
		int f = i;
		while(tokens[f].value)
		{
			free(tokens[f].value);
			f++;
		}
		tokens[i].value= ft_strdup(sp[0]);
		i++;
		tokens[i].value = ft_strdup(&val);
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
		return(tokens);
}

s_token	*ft_r_sep_sng(s_token *tokens, int i, char val,char	**tmp_tokens, int tmp)
{
		char **sp;
		sp = ft_split(tokens[i].value, val);
		int f = i;
		while(tokens[f].value)
		{
			free(tokens[f].value);
			f++;
		}
		tokens[i].value =ft_strdup(&val);
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

s_token	*ft_l_sep_sng(s_token *tokens, int i, char val, char	**tmp_tokens, int tmp)
{
	char **sp;
	sp = ft_split(tokens[i].value, val);
	int f = i;
	while(tokens[f].value)
	{
		free(tokens[f].value);
		f++;
	}
	tokens[i].value = ft_strdup(sp[0]);
	i++;
	tokens[i].value =ft_strdup(&val);
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
	free(tmp_tokens);;
	return(tokens);
}
s_token *ft_single_sep(s_token *tokens, int i, int j, char val)
{
	char	**tmp_tokens;
	int		tmp;

	tmp_tokens = ft_tmp_tokens(tokens);
	tmp = i + 1;

	if(j != 0 && tokens[i].value[j+2])
	{
		tokens = ft_r_l_sep_sng(tokens,i,val,tmp_tokens, tmp);
		return(tokens);
	}
	else if(tokens[i].value[j+2])
	{
		tokens = ft_r_sep_sng(tokens,i,val,tmp_tokens, tmp);	
		return(tokens);
	}
	else if(j != 0)
	{
		tokens = ft_l_sep_sng(tokens,i,val,tmp_tokens, tmp);
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