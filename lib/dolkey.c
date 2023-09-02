/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolkey.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:04:01 by maygen            #+#    #+#             */
/*   Updated: 2023/09/02 14:45:33 by maygen           ###   ########.fr       */
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

static	int	ft_isdigit(int a)
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

static	long	digit(long num)
{
	int	i;

	i = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		i++;
	while (num)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*mystr;
	int		a;
	long	nb;

	nb = n;
	a = digit(nb);
	mystr = (char *)malloc(a + 1);
	if (!mystr)
		return (NULL);
	if (n < 0)
	{
		nb *= -1;
		mystr[0] = '-';
	}
	mystr[a] = '\0';
	a--;
	while ((n < 0) <= a)
	{
		mystr[a] = (nb % 10) + 48;
		nb /= 10;
		a--;
	}
	return (mystr);
}
