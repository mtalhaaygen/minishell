/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:41:44 by maygen            #+#    #+#             */
/*   Updated: 2023/08/26 17:05:54 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_env(char *arg)
{
	int		i;
	char	**s;
	s_env	*nenv;

	i = -1;
	nenv = malloc(sizeof(s_env) * g_va->env->env_count + 1);
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
	int i;

	i = -1;
	while (args[++i])
		printf("declare -x %s\n", args[i]);
}

void	ft_export1(Node node)
{
	// if (node.args[1] == NULL) 
	// command : export, command : export | grep a, parametresiz
	// printf("deneme\n");
	(void)node;
	ft_print_full(g_va->full);
	exit(0);
}

void	ft_export2(Node node)
{
	// parametresi varken ve process_count 1 iken gelecek buraya
	if (g_va->process_count == 1) //bu if i daha önce atmışız ama kalsın önemi yok|| export a=1 gibi pipe yokken parametreli
	{
		char	**new;
		int		i;
		int		args_index;

		i = -1;
		args_index = 0;
		g_va->full_size = arg_count(g_va->full) + node.arg_count - 1;
		new = malloc(sizeof(char *) * g_va->full_size + 1);
		while (g_va->full[++i])
			new[i] = ft_strdup(g_va->full[i]);
		while (node.args[++args_index])
			new[i++] = ft_strdup(node.args[args_index]);
		new[i] = NULL;
		g_va->full = new;
		args_index = 0;
		while (node.args[++args_index] && ft_strfind(node.args[args_index], '='))
			add_env(node.args[args_index]);
		// insertionSort(g_va->full, g_va->full_size);
	}
}
