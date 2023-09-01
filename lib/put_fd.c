/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:47:28 by maygen            #+#    #+#             */
/*   Updated: 2023/09/01 18:19:58 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_pp(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		free(args[i]);
	free(args);
}

void	ft_perror(const char *str)
{
	write(1, "tsh: ", 6);
	perror(str);
}

void	insertionSort(char** arr, int size)
{
	char	*key;
	size_t	len;
	int		j;
	int		i;

	i = 1;
	while (++i < size)
	{
		key = arr[i];
		j = i - 1;
		len = ft_strlen(key);
		if (len > ft_strlen(arr[j]))
			len = ft_strlen(arr[j]);
		while (j >= 0 && ft_strncmp_signed(arr[j], key, len) > 0)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;
	char	x;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		x = s[i];
		write(fd, &x, 1);
		i++;
	}
}

int	ft_strfind(char	*str, int c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i + 1);
	return (0);
}
