/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:29:13 by maygen            #+#    #+#             */
/*   Updated: 2023/08/28 17:03:01 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_full(char *new)
{
	int	size;
	int	len;

	len = ft_strfind(new, '=');
	if (len == 0)
		len = ft_strlen(new);
	else
		len--;
	size = g_va->full_size - 1;
	while (size > 0)
	{
		if (ft_strncmp(new, g_va->full[size], len) && \
				(new[len] == '=' || new[len] == '\0'))
			return (1);
		size--;
	}
	return (0);
}
