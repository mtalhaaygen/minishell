/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_merge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:04:22 by maygen            #+#    #+#             */
/*   Updated: 2023/08/22 17:49:46 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_process_merge(int i)
{
	if (g_va->process_count != 1 && g_va->nodes[g_va->process_count - 1].args[0])
	{
		if (i != g_va->process_count - 1)
			dup2(g_va->process[i].fd[1], STDOUT_FILENO);
		if (i != 0)
			dup2(g_va->process[i - 1].fd[0], STDIN_FILENO);

		pipe_close();
	}
}

void	pipe_close()
{
	if (g_va->process_count != 1 && g_va->nodes[g_va->process_count - 1].args[0])
	{
		int	i;

		i = 0;
		while (i < g_va->process_count - 1)
		{
			close(g_va->process[i].fd[0]);
			close(g_va->process[i].fd[1]);
			i++;
		}
	}
}