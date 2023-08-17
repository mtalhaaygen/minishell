/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:56:16 by maygen            #+#    #+#             */
/*   Updated: 2023/08/17 18:56:19 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(char *src)
{
	char	*new;
	int		i;

	i = 0;
	if (!src)
		return (0);
	while (src[i])
		i++;
	new = ft_calloc(sizeof(char), (i + 1));
	if (!new)
		return (0);
	while (i >= 0)
	{
		new[i] = src[i];
		i--;
	}
	
	return (new);
}

char	*ft_strdup_dolkey(char *src)
{
	char	*new;
	int		i;

	i = 0;
	if (!src)
		return (0);
	while (src[i])
		i++;
	new = ft_calloc(sizeof(char), (i + 1));
	if (!new)
		return (0);
	while (i >= 0)
	{
		new[i] = src[i];
		i--;
	}
	free(src);
	return (new);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	unsigned int	i;
	size_t			j;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		len = ft_strlen(s) - start;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			ptr[j++] = s[i];
		}
		i++;
	}
	ptr[j] = '\0';
	return (ptr);
}

static size_t	ft_word_count(char const *s, char c)
{
	size_t	i;
	size_t	rtn;

	i = 0;
	rtn = 0;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != 0)
			rtn++;
		i++;
	}
	if (s[0] != c)
		rtn++;
	return (rtn);
}

static char	**protect(void)
{
	char	**rtn;

	rtn = malloc(sizeof(char *));
	rtn[0] = NULL;
	return (rtn);
}

char	**ft_split(char const *s, char c)
{
	char	**rtn;
	size_t	word_count;
	size_t	i;
	size_t	j;
	size_t	flag;

	i = 0;
	j = 0;
	if (!s || s[0] == 0)
		return (protect());
	word_count = ft_word_count(s, c);
	rtn = malloc(sizeof(char *) * (word_count + 1));
	if (!rtn)
		return (NULL);
	while (i < word_count)
	{
		while (s[j] == c)
			j++;
		flag = j;
		while (s[j] != c && s[j])
			j++;
		rtn[i++] = ft_substr(s, flag, j - flag);
	}
	rtn[i] = NULL;
	return (rtn);
}
