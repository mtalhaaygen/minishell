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
				tokens = ft_double_sep(tokens, i, j,tokens[i].value[j]);
				i++;
			}
            else if(tokens[i].value[j] == '<' && !tokens[i].quot_flag)
			{
               	tokens = ft_single_sep(tokens, i, j,tokens[i].value[j]);

				i++;
			}
			else if(tokens[i].value[j] == '>' && tokens[i].value[j+1] == '>' && !tokens[i].quot_flag)
			{
				tokens = ft_double_sep(tokens, i, j,tokens[i].value[j]);
				i++;
			}
            else if(tokens[i].value[j] == '>' && !tokens[i].quot_flag)
			{
                tokens = ft_single_sep(tokens, i, j,tokens[i].value[j]);
				i++;
			}
            else if (tokens[i].value[j] == '|' && !tokens[i].quot_flag)
			{
				tokens = ft_single_sep(tokens, i, j,tokens[i].value[j]);
				i++;
			}
			j++;
		}
		i++;
	}
	return (tokens);
}