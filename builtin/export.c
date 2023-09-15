/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:41:44 by maygen            #+#    #+#             */
/*   Updated: 2023/09/15 18:12:55 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_env(char *arg)
{
	int		i;
	char	**s;
	t_env	*nenv;

	i = -1;
	nenv = malloc(sizeof(t_env) * ft_envadd_counter());
	nenv->env_count = g_va->env->env_count + 1;
	while (g_va->env[++i].key)
	{
		nenv[i].key = ft_strdup(g_va->env[i].key);
		nenv[i].value = ft_strdup(g_va->env[i].value);
	}
	s = ft_split(arg, '=');
	nenv[i].key = ft_strdup(s[0]);
	nenv[i].value = ft_strdup(s[1]);
	free_pp(s);
	i = -1;
	while (g_va->env[++i].key)
	{
		free(g_va->env[i].key);
		free(g_va->env[i].value);
	}
	free(g_va->env);
	g_va->env = nenv;
}

void	full_update(char	*new)
{
	int	len;
	int	i;

	i = -1;
	len = ft_strfind(new, '=');
	if (len == 0)
		len = ft_strlen(new);
	else
		len--;
	while (g_va->full[++i])
	{
		if (ft_strncmp(new, g_va->full[i], len) && \
				(new[len] == '=' || new[len] == '\0'))
		{
			free(g_va->full[i]);
			g_va->full[i] = ft_strdup(new);
		}
	}
}

void	env_update(char	*new)
{
	int		size;
	int		len;
	char	**s;

	size = g_va->env->env_count - 1;
	while (size > 0 && g_va->env[size].key)
	{
		len = ft_strlen(g_va->env[size].key);
		if (ft_strncmp(new, g_va->full[size], len) && \
				(new[len] == '=' || new[len] == '\0'))
		{
			s = ft_split(new, '=');
			free(g_va->env[size].value);
			g_va->env[size].value = ft_strdup(s[1]);
			free_pp(s);
			break ;
		}
		size--;
	}
	if (size == 0 && ft_strfind(new, '='))
		add_env(new);
}

void	ft_add_export(t_node node)
{
	int		i;
	int		args_index;
	char	**new;

	i = -1;
	args_index = 0;
	while (node.args[++args_index]
		&& ft_strfind(node.args[args_index], '='))
	{
		if (!find_full(node.args[args_index]))
			add_env(node.args[args_index]);
	}
	g_va->full_size = arg_count(g_va->full) + node.arg_count - 1;
	new = malloc(sizeof(char *) * g_va->full_size + 1);
	while (g_va->full[++i])
		new[i] = ft_strdup(g_va->full[i]);
	args_index = 0;
	while (node.args[++args_index])
	{
		if (!find_full(node.args[args_index]))
			new[i++] = ft_strdup(node.args[args_index]);
	}
	new[i] = NULL;
	free_pp(g_va->full);
	g_va->full = new;
}

void	ft_export2(t_node node)
{
	int		args_index;

	if (g_va->process_count == 1)
	{
		args_index = 0;
		while (node.args[++args_index])
		{
			if (ft_strfind(node.args[args_index], '=')
				&& find_full(node.args[args_index]))
			{
				full_update(node.args[args_index]);
				env_update(node.args[args_index]);
				node.arg_count--;
			}
		}
		if (node.arg_count <= 1)
			return ;
		ft_add_export(node);
	}
}
