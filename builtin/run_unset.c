/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:12:19 by maygen            #+#    #+#             */
/*   Updated: 2023/09/03 17:03:20 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_env(int index)
{
	int		i;
	t_env	*nenv;

	i = -1;
	nenv = malloc(sizeof(t_env) * g_va->env->env_count);
	nenv->env_count = g_va->env->env_count - 1;
	while (g_va->env[++i].key)
	{
		if (i < index)
		{
			nenv[i].key = g_va->env[i].key;
			nenv[i].value = g_va->env[i].value;
		}
		if (i > index)
		{
			nenv[i - 1].key = g_va->env[i].key;
			nenv[i - 1].value = g_va->env[i].value;
		}
	}
	nenv[i - 1].key = NULL;
	nenv[i - 1].value = NULL;
	g_va->env = nenv;
}

void	del_full(int index)
{
	char	**new;
	int		i;

	i = -1;
	g_va->full_size = g_va->full_size - 1;
	new = malloc(sizeof(char *) * g_va->full_size + 1);
	while (g_va->full[++i])
	{
		if (i < index)
			new[i] = ft_strdup(g_va->full[i]);
		if (i > index)
			new[i - 1] = ft_strdup(g_va->full[i]);
	}
	new[i - 1] = NULL;
	g_va->full = new;
}

void	run_unset(t_node node)
{
	int	i;
	int	size;
	int	len;

	if (node.arg_count > 1)
	{
		i = 0;
		while (node.args[++i])
		{
			len = ft_strlen(node.args[i]);
			size = g_va->env->env_count - 1;
			while (size > 0)
			{
				if (ft_strcmp(node.args[i], g_va->env[size].key))
				{
					del_env(size);
					break ;
				}
				size--;
			}
			size = g_va->full_size;
			while (size > 0)
			{
				if (ft_strncmp(node.args[i], g_va->full[size], len) && \
						(node.args[i][len] == '=' || node.args[i][len] == '\0'))
					del_full(size);
				size--;
			}
		}
	}
	// update $? =0
}
