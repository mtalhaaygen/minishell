/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:57:32 by tdemir            #+#    #+#             */
/*   Updated: 2023/08/22 17:10:33 by maygen           ###   ########.fr       */
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
	char *dol_null;
	dol_null = ft_calloc(2,sizeof(char));
	dol_null[0] = '$';
	dol_null[1] = '\0';
	if(dolkey[0] == '$' && !dolkey[1])
		return(dol_null);
	while (g_va.env[i].key)
	{
		if (ft_strcmp(dolkey, g_va.env[i].key))
			return (g_va.env[i].value);
		i++;
	}
	free(dol_null);
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
			if (tokens[i].value[j] == '$' && tokens[i].fq == 0)
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
