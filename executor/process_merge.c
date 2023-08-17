/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_merge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:04:22 by maygen            #+#    #+#             */
/*   Updated: 2023/08/17 19:22:23 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_process_merge(int i)
{
	if (gv.process_count != 1 && gv.nodes[gv.process_count - 1].args[0])
	{
		if (i != gv.process_count - 1)
			dup2(gv.process[i].fd[1], STDOUT_FILENO);
		if (i != 0)
			dup2(gv.process[i - 1].fd[0], STDIN_FILENO);

		pipe_close();
	}
}

void	pipe_close()
{
	if (gv.process_count != 1 && gv.nodes[gv.process_count - 1].args[0])
	{
		int	i;

		i = 0;
		while (i < gv.process_count - 1)
		{
			close(gv.process[i].fd[0]);
			close(gv.process[i].fd[1]);
			i++;
		}
	}
}