/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:58:35 by maygen            #+#    #+#             */
/*   Updated: 2023/07/29 16:59:56 by maygen           ###   ########.fr       */
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
	}
	else
		run_builtin(status);
	return (0);
}