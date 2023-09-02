/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:41:44 by maygen            #+#    #+#             */
/*   Updated: 2023/09/02 16:33:48 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_env(char *arg)
{
	int		i;
	char	**s;
	t_env	*nenv;

	i = -1;
	nenv = malloc(sizeof(t_env) * g_va->env->env_count + 1);
	nenv->env_count = g_va->env->env_count + 1;
	while (g_va->env[++i].key)
	{
		nenv[i].key = g_va->env[i].key;
		nenv[i].value = g_va->env[i].value;
	}
	s = ft_split(arg, '=');
	nenv[i].key = s[0];
	nenv[i].value = s[1];
	g_va->env = nenv;
}

void	ft_print_full(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		printf("declare -x %s\n", args[i]);
}

	// ilk başta "export a" gibi value atamadan eklendiğinde update edemiyor
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
			// printf("update full %s\n", g_va->full[i]);
			g_va->full[i] = ft_strdup(new);
		}
	}
	printf("fulll update new:%s\n", new);
}

void	env_update(char	*new)
{
	int	size;
	int	len;

	size = g_va->env->env_count - 1;
	while (size > 0 && g_va->env[size].key)
	{
		len = ft_strlen(g_va->env[size].key);
		// printf("key:%s // new:%s // len:%d\n", g_va->env[size].key, new, len);
		if (ft_strncmp(new, g_va->full[size], len) && \
				(new[len] == '=' || new[len] == '\0'))
		{
			// printf("update env %s\n", g_va->env[size].key);
			char **s;
			s = ft_split(new, '=');
			g_va->env[size].value = ft_strdup(s[1]);
		}
		size--;
	}
}

// parametresi varken ve process_count 1 iken gelecek buraya
// bu if i daha önce atmışız ama kalsın önemi yok|| export a=1 gibi 
// pipe yokken parametreli
void	ft_export2(Node node)
{
	char	**new;
	int		i;
	int		args_index;

	if (g_va->process_count == 1)
	{
		i = -1;
		args_index = 0;
		while (node.args[++args_index])
		{
			if (find_full(node.args[args_index]))
			{
				full_update(node.args[args_index]);
				env_update(node.args[args_index]);
				node.arg_count--;
			}
		}
		args_index = 0;
		while (node.args[++args_index] && ft_strfind(node.args[args_index], '='))
		{
			if (!find_full(node.args[args_index]))
				add_env(node.args[args_index]);
		}
		args_index = 0;
		g_va->full_size = arg_count(g_va->full) + node.arg_count - 1;
		new = malloc(sizeof(char *) * g_va->full_size + 1);
		printf("3333333333\n");
		while (g_va->full[++i])
			new[i] = ft_strdup(g_va->full[i]);
		while (node.args[++args_index])
		{
			if (!find_full(node.args[args_index]))
				new[i++] = ft_strdup(node.args[args_index]);
		}
		new[i] = NULL;
		printf("444444444\n");
		g_va->full = new;
		// insertionSort(g_va->full, g_va->full_size);
		printf("export2 completed\n");
	}
}
