/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:41:44 by maygen            #+#    #+#             */
/*   Updated: 2023/08/22 17:08:28 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ft_print_full()
{
	int i;

	i = 0;
	while (g_va.full[i])
	{
		printf("declare -x %s\n", g_va.full[i]);
		i++;
	}
	printf("ekrana basılan:%d // g_va.full_size:%d\n", i, g_va.full_size);
}

void ft_export(Node node)
{
	if (node.args[1] == NULL) // command : export, command : export | grep a, parametresiz
		ft_print_full();
	else if (g_va.process_count == 1) // export a=1, pipe yokken parametreli
	{
		char	**new;
		int		i;

		i = -1;
		g_va.full_size = arg_count(g_va.full) + 1;
		printf("içerde fullsize:%d\n", g_va.full_size);
		new = ft_calloc(g_va.full_size + 1, sizeof(char *));
		if (!new)
			return ;
		while (g_va.full[++i])
			new[i] = g_va.full[i];
		new[i] = node.args[1];
		g_va.full = new;
		printf("add full %s\n", node.args[1]);
		insertionSort(g_va.full, g_va.full_size);
	}
	// parametresi varken ve pipe varken çalışmayacak direkt exit
	exit(0);
}
