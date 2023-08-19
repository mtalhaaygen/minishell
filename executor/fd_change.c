/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_change.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:09:48 by maygen            #+#    #+#             */
/*   Updated: 2023/08/18 20:05:25 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// bu fonksiyon dosya izinlerini kontrol edecek gerekirse gerekli hata kodlarını ekrana basacak
int		file_access(char	*filename, int flag)
{
	// cat <main.c   main.c infile oluyor 
	//infile olan dosyalar okunabilir mi bakacağız R_OK
	// ls >deneme.txt gibi bir durumda yada append de (>>) access kontrolüne gerek yok
	// diğerlerini çalıştırılabilir mi diye bakacağız
	if (access(filename, flag) == 0)
		return (1);
	else
	{
		if (errno == EACCES)
			perror(filename);
			// printf("%s: Permission denied\n", filename);
		else if (errno == ENOENT)
			perror(filename);
			// printf("%s: No such file or directory\n", filename);
		else
			perror("access");
	}
	return (0);
}

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
		if (file_access(node.infile->name, R_OK) == 0)
			exit(2);
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
	// while içerisinde tüm node dolaşılacak ilk redirection ile change fd ve change node yapılacak, sonra diğer redirection için aynısı yapılacak
	// ls > deneme.txt > txt > t.txt outfile=NULL stdout
	// ls > txt > t.txt outfile=deneme.txt
	// ls > t.txt outfile=txt
	// ls outfile=t.txt 
	// şeklinde her redirectionu gördüğünde infile outfile değişecek, her redirection gördüğünde gerekli fd dup2 ile yeni fd ye aktarılacak
	int index;

	if ((index = contain_i(nodes[i].args)))
		change_fd_i(nodes[i], index);
	else if ((index = contain_ii(nodes[i].args)))
		change_fd_ii(nodes[i], index);
	else if ((index = contain_o(nodes[i].args)))
		change_fd_o(nodes[i], index);
}
