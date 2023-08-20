/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:57:32 by tdemir            #+#    #+#             */
/*   Updated: 2023/08/20 17:22:38 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_dolkey(s_token *tokens, int i, int j)
{
	char	*dolkey;
	int		len;
	int		tmp;
	int		k; 

	j++;
	len = 0;
	k = 0;
	tmp = j;
	while (tokens[i].value[tmp] && tokens[i].value[tmp] != 39)
	{
		tmp++;
		len++;
	}
	dolkey = ft_calloc(len + 1, sizeof(char));
	while (tokens[i].value[j] && tokens[i].value[j] != 39)
	{
		dolkey[k] = tokens[i].value[j];
		k++;
		j++;
	}
	dolkey[k] = '\0';
	// printf("kjsd %p\n", dolkey);
	return (dolkey);
}

char	*ft_dolval(char *dolkey)
{
	int	i;

	i = 0;
	while (gv.env[i].key)
	{
		if (ft_strcmp(dolkey, gv.env[i].key))
			return (gv.env[i].value);
		i++;
	}
	return (0);
}

void ft_change_token( char *dolval, s_token *tokens, int i, int j)
{
	int		len;
	char	*str;
	int		k;
	int		s;

	len = 0;
	s = 0;
	k = 0;
	while (tokens[i].value[len] != '$')
		len++;
	if (dolval != 0)
		len += ft_strlen(dolval);
	str = ft_calloc(len+3, sizeof(char));
	while (k < j)
	{
		str[k] = tokens[i].value[k];
		k++;
	}
	while (dolval[s])
	{
		str[k] = dolval[s];
		k++;
		s++;
	}
	str[k] = '\0';
	free(tokens[i].value );
	tokens[i].value = ft_strdup(str);
	free(str);

}
void ft_wod(s_token *tokens, int i)
{
	int		len;
	char	*str;

	len = 0;
	while (tokens[i].value[len] != '$')
		len++;
	str = ft_calloc(len + 1, sizeof(char));
	len = 0;
	while (tokens[i].value[len] != '$')
	{
		str[len] = tokens[i].value[len];
		len++;
	}
	str[len] = '\0';
	free(tokens[i].value);
	tokens[i].value = ft_strdup_dolkey(str);
}

s_token	*ft_dollar(s_token *tokens)
{
	int		i;
	int		j;
	char	*dolkey;
	char	*dolval;

	i = -1;
	while (tokens[++i].value)
	{

		j = -1;
		while (tokens[i].value[++j] != '\0')
		{
			if (tokens[i].value[j] == '$' && tokens[i].value[j - 1] != 39)
			{
				dolkey = ft_strdup_dolkey(ft_dolkey(tokens, i, j));
				if (ft_dolval(dolkey))
				{
					dolval = ft_strdup(ft_dolval(dolkey));
					ft_change_token (dolval, tokens, i, j);
					free(dolval);
				}
				else
					ft_wod (tokens, i);	
				free(dolkey);			
			}
		}

	}					
	



	return (tokens);
}
