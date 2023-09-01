/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_change.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:09:48 by maygen            #+#    #+#             */
/*   Updated: 2023/09/01 14:15:57 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fd_change(Node node, int index)
{
	while (node.args[index] && node.args[index + 2])
	{
		// free(node.args[index]);
		node.args[index] = node.args[index + 2];
		index++;
	}
	// free(node.args[index]);
	// free(node.args[index + 1]);
	node.args[index] = NULL;
	node.args[index + 1] = NULL;
}

// dosya var >> izni kontrol et >>> izni yok >>> permission denided EXİT
// dosya var >> izni kontrol et >>> izni var >>> open ile aç dup2 fd_change
// dosya yok >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> open ile aç dup2 fd_change
void	change_fd_i(Node node, int index)
{
	int	fdnewtxt;

	if (node.outfile->name != NULL)
	{
		if (access(node.args[index + 1], F_OK) != -1)
			file_access(node.args[index + 1], W_OK);
		fdnewtxt = open(node.args[index + 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (ft_strcmp(node.outfile->name, node.args[index + 1]))
			dup2(fdnewtxt, STDOUT_FILENO);
		fd_change(node, index);
	}
}

// -rw-r--r--  644
void	change_fd_ii(Node node, int index)
{
	int	fdnewtxt;

	if (node.outfile->name != NULL)
	{
		if (access(node.args[index + 1], F_OK) != -1)
			file_access(node.args[index + 1], W_OK);
		fdnewtxt = open(node.args[index + 1], \
					O_RDWR | O_APPEND | O_CREAT, 0644);
		if (ft_strcmp(node.outfile->name, node.args[index + 1]))
			dup2(fdnewtxt, STDOUT_FILENO); 
		fd_change(node, index);
	}
}

void	change_fd_o(Node node, int index)
{
	int	fdnewtxt;

	if (node.infile->name != NULL)
	{
		if (file_access(node.args[index + 1], R_OK) == 0)
			exit(2);
		fdnewtxt = open(node.args[index + 1], O_RDWR, 0777);
		if (ft_strcmp(node.infile->name, node.args[index + 1]))
			dup2(fdnewtxt, STDIN_FILENO);
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
void	is_redirection(Node *nodes, int i)
{
	int	j;

	j = -1;
	while (nodes[i].args[++j])
	{
		if (ft_strcmp(">", nodes[i].args[j]))
		{
			change_fd_i(nodes[i], j);
			j -= 1;
		}
		else if (ft_strcmp(">>", nodes[i].args[j]))
		{
			change_fd_ii(nodes[i], j);
			j -= 1;
		}
		else if (ft_strcmp("<", nodes[i].args[j]))
		{
			change_fd_o(nodes[i], j);
			j -= 1;
		}
	}
}
