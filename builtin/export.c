/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:41:44 by maygen            #+#    #+#             */
/*   Updated: 2023/08/25 10:09:51 by maygen           ###   ########.fr       */
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

void	ft_export1(Node node)
{
	if (node.args[1] == NULL) // command : export, command : export | grep a, parametresiz
	{
		ft_print_full(g_va->full);
		exit(0);
	}
}

void	ft_export2(Node node)
{
	// parametresi varken ve process_count 1 iken gelecek buraya
	if (g_va->process_count == 1) //bu if i daha önce atmışız ama kalsın önemi yok|| export a=1 gibi pipe yokken parametreli
	{
		/**
		 * EXPORT hem full e hemde env içine ekleyebilir olacak
		 * 
		 */
		char	**new;
		int		i;

		i = -1;
		g_va->full_size = arg_count(g_va->full) + 1;
		// printf("ad:%p\n", &g_va->full_size);
		new = malloc(sizeof(char *) * g_va->full_size + 1);
		while (g_va->full[++i])
			new[i] = ft_strdup(g_va->full[i]);
		new[i] = ft_strdup(node.args[1]);
		new[++i] = NULL;
		g_va->full = new;
		printf("add full %s\n", node.args[1]);
		// insertionSort(g_va->full, g_va->full_size);
	}
}
