/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolkey.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:04:01 by maygen            #+#    #+#             */
/*   Updated: 2023/09/01 12:47:51 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	ft_isdigit(int a)
{
	if ((a <= 57 && a >= 48))
		return (1);
	return (0);
}

int	ft_number(char	*str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (!ft_isdigit(str[i]))
		{
			if ((str[i] != '-' && str[i] != '+' && str[i] != ' ') || \
			((str[i] == '-' || str[i] == '+' ) && (str[i + 1] == ' ' || \
			str[i + 1] == '+' || str[i + 1] == '-' )))
				return (0);
		}
		i++;
	}
	return (1);
}
