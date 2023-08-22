/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:41:44 by maygen            #+#    #+#             */
/*   Updated: 2023/08/22 19:53:56 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ft_print_full(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		printf("declare -x %s\n", args[i]);
		i++;
	}
	printf("ekrana basılan:%d // g_va->full_size:%d\n", i, g_va->full_size);
	printf("ad:%p\n", &g_va->full_size);
}

void ft_export(Node node)
{
	if (node.args[1] == NULL) // command : export, command : export | grep a, parametresiz
		ft_print_full(g_va->full);
	else if (g_va->process_count == 1) // export a=1, pipe yokken parametreli
	{
		char	**new;
		int		i;

		i = -1;
		g_va->full_size = arg_count(g_va->full) + 1;
		printf("ad:%p\n", &g_va->full_size);
		new = ft_calloc(g_va->full_size + 1, sizeof(char *));
		if (!new)
			return ;
		while (g_va->full[++i])
			new[i] = ft_strdup(g_va->full[i]);
		new[i] =ft_strdup(node.args[1]);
		//fill_full(new, i);
		i = 0;
		while (new[i])
		{
			g_va->full[i] = new[i];
			i++;
		}
		
		g_va->full[i] = NULL;
		printf("add full %s\n", node.args[1]);
		insertionSort(g_va->full, g_va->full_size);
	}
	// parametresi varken ve pipe varken çalışmayacak direkt exit
	exit(0);
}
