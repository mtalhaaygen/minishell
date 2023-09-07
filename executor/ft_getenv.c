/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:27:19 by maygen            #+#    #+#             */
/*   Updated: 2023/09/07 19:27:25 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *str)
{
	int	size;
	int	len;

	len = ft_strfind(str, '=');
	if (len == 0)
		len = ft_strlen(str);
	else
		len--;
	size = g_va->full_size - 1;
	while (size > 0)
	{
		if (ft_strncmp(str, g_va->full[size], len) && \
					(str[len] == '=' || str[len] == '\0'))
			return (g_va->full[size] + len);
		size--;
	}
	return (NULL);
}