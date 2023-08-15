/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:44:48 by maygen            #+#    #+#             */
/*   Updated: 2023/08/15 12:42:42 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memset(void *src, int c, size_t len)
{
	size_t	i;
	char	*src1;

	i = 0;
	src1 = (char *)src;
	if (!src && !len)
		return (NULL);
	while (i < len)
	{
		src1[i] = c;
		i++;
	}
	return (src);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

char	*ft_readline(char *str)
{
	char	*buf;

	write(1, "\033[7m\033[1;36m", 12);
	write(1, "talha@minishell", 16);
	write(1, "\033[0m\033[33m", 10);
	buf = readline(str);
	return (buf);
}

int	my_isspace(char ch)
{
	if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' \
		|| ch == '\f' || ch == '\v')
		return (1);
	return (0);
}
