/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:41:44 by maygen            #+#    #+#             */
/*   Updated: 2023/08/21 13:22:15 by maygen           ###   ########.fr       */
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
}

void ft_export(Node node)
{
	if (node.args[1] == NULL) // command : export, command : export | grep a, parametresiz
		ft_print_full();
	else if (gv.process_count == 1) // export a=1, pipe yokken parametreli
	{
		printf("add full %s\n", node.args[1]);
	}
	// parametreli ve pipe varken çalışmayacak direkt exit
	exit(0);
}
