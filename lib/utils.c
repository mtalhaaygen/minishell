/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:44:48 by maygen            #+#    #+#             */
/*   Updated: 2023/09/10 21:04:17 by maygen           ###   ########.fr       */
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

	g_va->syn_err = 0;
	write(1, "\033[7m\033[1;36m", 12);
	write(1, "talha@minishell", 16);
	write(1, "\033[0m\033[1;33m", 12);
	buf = readline(str);
	write(1, "\033[0m", 5);
	if (!buf)
	{
		write(1, "\033[D\033[D", 7);
		printf("exit\n");
		exit(1);
	}
	return (buf);
}

int	my_isspace(char ch)
{
	if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' \
		|| ch == '\f' || ch == '\v')
		return (1);
	return (0);
}
