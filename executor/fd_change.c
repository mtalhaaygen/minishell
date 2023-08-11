/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_change.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:09:48 by maygen            #+#    #+#             */
/*   Updated: 2023/08/11 14:28:33 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	is_heredoc(Node *nodes, int index)
// {
// 	int	i;

// 	i = -1;
// 	while (nodes[index].args[++i])
// 	{
// 		if (ft_strcmp("<<", nodes[index].args[i]))
// 			return (1);
// 	}
// 	return (0);
// }

void	is_redirection(char *command, int i)
{
	int index;

	if((index = contain_i(nodes[i].args)))
		change_fd_i(nodes[i], index)
	if((index = contain_ii(nodes[i].args)))
		change_fd_ii(nodes[i], index);
	if((index = contain_o(nodes[i].args)))
		change_fd_o(nodes[i], index);
}




/*
// // int is_redirection(Node *nodes)
// // {
// // 	int	i;
// // 	int index;
// // 	int	status;

// // 	i = 0;
// // 	while (nodes[i].args[0])
// // 	{
// // 		if((index = contain_heredoc(nodes[i].args, i)))
// // 			ft_executor_heredoc(nodes, index);
// // 		if((index = contain_i(nodes[i].args)))
// // 			change_fd_i(nodes, index)
// // 		if((index = contain_ii(nodes[i].args)))
// // 			change_fd_ii(nodes, index);
// // 		if((index = contain_o(nodes[i].args)))
// // 			change_fd_o(nodes, index);
// // 	}
// // }

*/
