/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_merge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:04:22 by maygen            #+#    #+#             */
/*   Updated: 2023/09/11 18:24:18 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_process_merge(int i)
{
	if (g_va->process_count != 1 \
			&& g_va->nodes[g_va->process_count - 1].args[0])
	{
		if (i != g_va->process_count - 1)
			dup2(g_va->process[i].fd[1], STDOUT_FILENO);
		if (i != 0)
			dup2(g_va->process[i - 1].fd[0], STDIN_FILENO);
		pipe_close();
	}
}

void	pipe_close(void)
{
	int	i;

	if (g_va->process_count != 1 \
			&& g_va->nodes[g_va->process_count - 1].args[0])
	{
		i = 0;
		while (i < g_va->process_count - 1)
		{
			close(g_va->process[i].fd[0]);
			close(g_va->process[i].fd[1]);
			i++;
		}
		free(g_va->process);
	}
}
