/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_change.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:09:48 by maygen            #+#    #+#             */
/*   Updated: 2023/09/14 19:33:42 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fd_change(t_node node, int index)
{
	while (node.args[index] && node.args[index + 2])
	{
		node.args[index] = node.args[index + 2];
		index++;
	}
	while (node.args[index])
	{
		node.args[index] = NULL;
		index++;
	}
}

// dosya var >> izni kontrol et >>> izni yok >>> permission denided EXİT
// dosya var >> izni kontrol et >>> izni var >>> open ile aç dup2 fd_change
// dosya yok >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> open ile aç dup2 fd_change
void	change_fd_i(t_node node, int index)
{
	int	fdnewtxt;

	if (node.outfile->name != NULL)
	{
		if (access(node.args[index + 1], F_OK) != -1)
			file_access(node.args[index + 1], W_OK, 7, node);
		fdnewtxt = open(node.args[index + 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (ft_strcmp(node.outfile->name, node.args[index + 1]))
		{
			dup2(fdnewtxt, STDOUT_FILENO);
			free(node.outfile->name);
			free(node.outfile);
		}
		fd_change(node, index);
	}
}

void	change_fd_ii(t_node node, int index)
{
	int	fdnewtxt;

	if (node.outfile->name != NULL)
	{
		if (access(node.args[index + 1], F_OK) != -1)
			file_access(node.args[index + 1], W_OK, 7, node);
		fdnewtxt = open(node.args[index + 1], \
					O_RDWR | O_APPEND | O_CREAT, 0644);
		if (ft_strcmp(node.outfile->name, node.args[index + 1]))
		{
			dup2(fdnewtxt, STDOUT_FILENO);
			free(node.outfile->name);
			free(node.outfile);
		}
		fd_change(node, index);
	}
}

void	change_fd_o(t_node node, int index)
{
	int	fdnewtxt;

	if (node.infile->name != NULL)
	{
		if (file_access(node.args[index + 1], R_OK, 10, node) == 0)
			return ;
		fdnewtxt = open(node.args[index + 1], O_RDWR, 0777);
		if (ft_strcmp(node.infile->name, node.args[index + 1]))
		{
			dup2(fdnewtxt, STDIN_FILENO);
			free(node.infile->name);
			free(node.infile);
		}
		fd_change(node, index);
	}
}

	// while içerisinde tüm node dolaşılacak ilk redirection ile change fd ve
	// change node yapılacak, sonra diğer redirection için aynısı yapılacak
	// ls > deneme.txt > txt > t.txt outfile=NULL stdout
	// ls > txt > t.txt outfile=deneme.txt
	// ls > t.txt outfile=txt
	// ls outfile=t.txt 
	// şeklinde her redirectionu gördüğünde infile outfile değişecek, 
	// her redirection gördüğünde gerekli fd dup2 ile yeni fd ye aktarılacak
	// > ve >> ifadeleri dosyaları istenildiği şekilde açacak eğer dosya
	// outfile ise o zaman dup2 ile STDOUT_FILENO yönlendirilecek
	// > >> yada < argümanından sonra herzaman dosya adı geldiği 
	// varsayılacak tüm argüman dizisini iki birim öne kaydırılıp son ikiye null
	// atılacak
void	is_redirection(t_node *nodes, int i)
{
	int	j;

	j = -1;
	while (nodes[i].args[++j])
	{
		if (ft_strcmp(">", nodes[i].args[j]) && nodes[i].args[j + 1])
		{
			change_fd_i(nodes[i], j);
			j -= 1;
		}
		else if (ft_strcmp(">>", nodes[i].args[j]) && nodes[i].args[j + 1])
		{
			change_fd_ii(nodes[i], j);
			j -= 1;
		}
		else if (ft_strcmp("<", nodes[i].args[j]) && nodes[i].args[j + 1])
		{
			change_fd_o(nodes[i], j);
			j -= 1;
		}
	}
}
