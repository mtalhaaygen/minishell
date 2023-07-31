/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:58:35 by maygen            #+#    #+#             */
/*   Updated: 2023/07/31 12:24:38 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_executor(Node *nodes)
{
	int status;
	
	status = is_builtin(nodes->args[0]);
	if (status == 0)
	{
		printf("execve\n");
		// execve komutu process i sonlandırdığından
		// pipe + 1 kadar fork yapılacak, tüm child processlerin pid i sanırsam 0 oluyor
		// child processlerde execve komutu çalıştırılacak
	}
	else
		run_builtin(status, nodes[0]);
	return (0);
}