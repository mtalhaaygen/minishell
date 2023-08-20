/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:41:44 by maygen            #+#    #+#             */
/*   Updated: 2023/08/20 15:19:18 by maygen           ###   ########.fr       */
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
	if (node.args[1] == NULL) // command : export, command : export | grep a
	{
		ft_print_full();
		exit(0);
	}
	else if (gv.process_count == 1) // export a=1
	{
		printf("add full\n");
		exit(0);
	}
	else if (gv.process_count > 1 && node.args[1] != NULL) // pipe varsa ve export parametresiz ise çalışmayacak command : export a=1 | grep 
		exit(0);
}
