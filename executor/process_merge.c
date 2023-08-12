/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_merge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:04:22 by maygen            #+#    #+#             */
/*   Updated: 2023/08/12 20:34:53 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_process_merge(int i)
{
	if (gv.process_count != 1) //pcount = 2 pipe sayısı 1 // ls | grep a
	{
		if (i == 0)
			dup2(gv.process[0].fd[1], STDOUT_FILENO);
		if (i == 1)
			dup2(gv.process[0].fd[0], STDIN_FILENO);
		close(gv.process[0].fd[1]);
		close(gv.process[0].fd[0]);
	}
}

void	pipe_close()
{
	if (gv.process_count != 1)
	{
		//int	i;

		// i = 0;
		// while (i < gv.process_count)
		// {
		// 	close(gv.process[i].fd[0]);
		// 	close(gv.process[i].fd[1]);
		// 	i++;
		// }
		close(gv.process[0].fd[0]);
		close(gv.process[0].fd[1]);
		
	}
}