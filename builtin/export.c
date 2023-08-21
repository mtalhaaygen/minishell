/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:41:44 by maygen            #+#    #+#             */
/*   Updated: 2023/08/21 18:30:12 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_full()
{
	int i;

	i = 0;
	while (gv.full[i])
	{
		printf("declare -x %s\n", gv.full[i]);
		i++;
	}
	printf("ekrana basılan:%d // gv.full_size:%d\n", i, gv.full_size);
}

void ft_export(Node node)
{
	if (node.args[1] == NULL) // command : export, command : export | grep a, parametresiz
		ft_print_full();
	else if (gv.process_count == 1) // export a=1, pipe yokken parametreli
	{
		char	**new;
		int		size;
		int		i;

		i = -1;
		size = arg_count(gv.full) + 1;
		
		gv.full_size = size;
		gv.full_size++;
		
		
		new = ft_calloc(size + 1, sizeof(char *));
		if (!new)
			return ;
		while (gv.full[i])
			new[i] = gv.full[i];
		new[i] = node.args[1];
		gv.full = new;
		printf("add full %s\n", node.args[1]);
		insertionSort(gv.full, gv.full_size);
	}
	// parametresi varken ve pipe varken çalışmayacak direkt exit
	exit(0);
}
