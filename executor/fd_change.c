/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_change.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:09:48 by maygen            #+#    #+#             */
/*   Updated: 2023/08/14 23:54:16 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_fd_i(Node node, int index)
{
	int	fdnewtxt;
	int	i;

	i = 0;
	// cat main.c > new.txt
	if (node.outfile->name != NULL) // >
	{
		fdnewtxt = open(node.outfile->name, O_RDWR | O_TRUNC | O_CREAT, 0777);
		dup2(fdnewtxt, STDOUT_FILENO);

//		node.args = ft_newargs(node.args);
 // cat talha.txt > deneme -e
 // yukarıdaki gibi bir komut için düşünürsek ">" ve "deneme" argümanlarını freeleyip NULL attık, -e argümanı args[4]te duruyor
 // gerekirse -e nin args[2] de durmasını sağlayacağız ve gerekecek
		// printf("CHANGE nodes\n[2]%s-[3]%s\n\n", node.args[2],node.args[3]);
		// node.args[1] = NULL;
		// node.args[2] = NULL;
		while (node.args[index + i] && i < 2)
		{
			free(node.args[index + i]);
			node.args[index + i] = NULL;
			i++;
		}
	}
}

void	change_fd_ii(Node node, int index)
{
	int	fdnewtxt;
	int	i;

	i = 0;
	if (node.outfile->name != NULL)
	{
		fdnewtxt = open(node.outfile->name, O_RDWR | O_APPEND | O_CREAT, 0777);
		dup2(fdnewtxt, STDOUT_FILENO);
		// aşağısı değişecek 
		while (node.args[index + i] && i < 2)
		{
			free(node.args[index + i]);
			node.args[index + i] = NULL;
			i++;
		}
	}
}

void	change_fd_o(Node node, int index)
{
	int	fdnewtxt;
	int	i;

	i = 0;
	if (node.infile->name != NULL)
	{
		fdnewtxt = open(node.infile->name, O_RDWR, 0777);
		dup2(fdnewtxt, STDIN_FILENO);
		while (node.args[index + i] && i < 2)
		{
			free(node.args[index + i]);
			node.args[index + i] = NULL;
			i++;
		}
	}
}

void	is_redirection(Node *nodes, int i)
{
	int index;
	if ((index = contain_i(nodes[i].args)))
		change_fd_i(nodes[i], index);
	else if ((index = contain_ii(nodes[i].args)))
		change_fd_ii(nodes[i], index);
	else if ((index = contain_o(nodes[i].args)))
		change_fd_o(nodes[i], index);
}
