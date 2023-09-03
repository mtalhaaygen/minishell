/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:29:13 by maygen            #+#    #+#             */
/*   Updated: 2023/09/03 11:12:50 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// tamamı redirection mu diye kontrol edecek
int	ft_find_redirection(Node node)
{
	int	i;

	i = -1;
	while (node.args[++i])
	{
		if (!ft_strncmp(">", node.args[i], 1))
			if (!ft_strncmp("<", node.args[i], 1))
				return (1);
	}
	return (0);
}

// bir node yalnızca redirection içeremez
// bit node boş olamaz
// yalnızca bir pipe varsa args[0] null olur, yalnızca > varsa 
// args[0] == > olur.
void	ft_syntax_error(Node *nodes)
{
	int	flag;
	int	i;

	i = -1;
	flag = 0;
	if (nodes[0].args[0] == NULL)
	{
		ft_perror("syntax error near unexpected token `|'\n");
		exit(258);
	}
	while (++i < g_va->process_count)
	{
		if (ft_find_redirection(nodes[i]))
		{
			flag = 2;
			break ;
		}
	}
	if (flag == 2)
		return ;
	if (flag == 0)
	{
		printf("aaatsh: syntax error near unexpected token `newline'\n");
		exit(258);
	}
}

int	find_full(char *new)
{
	int	size;
	int	len;

	len = ft_strfind(new, '=');
	if (len == 0)
		len = ft_strlen(new);
	else
		len--;
	size = g_va->full_size - 1;
	while (size > 0)
	{
		if (ft_strncmp(new, g_va->full[size], len) && \
				(new[len] == '=' || new[len] == '\0'))
			return (1);
		size--;
	}
	return (0);
}

int	file_access(char	*filename, int flag)
{
	if (access(filename, flag) == 0)
		return (1);
	else
	{
		if (errno == EACCES)
			perror(filename);
		else if (errno == ENOENT)
			perror(filename);
		else
			perror("access");
		exit(1);
	}
	return (0);
}

// export ?=123 şeklinde ekleme yapacak, tabii execve ile çalışmayacak 
// void	ft_export2(Node node) fonksiyonunu çağıracağız
// node.args içeriği aşağıdaki şekilde olacak
// export ?=err_number


// ilk başta bir ker "export ?=errnu" çalıştır yani export2(node)
// daha sonra direkt update_export fonk. çalıştır.

void	add_dollar_question_mark(void)
{
	Node	node;

	rm_heredoc();
	node.arg_count = 2;
	node.args = malloc(sizeof(char *) * 3);
	node.args[0] = ft_strdup("export");
	node.args[1] = ft_strdup(ft_strjoin("?=", ft_itoa(g_va->err_number)));
	// printf("*%s* added\n", node.args[1]);
	node.infile = NULL;
	node.outfile = NULL;
	ft_export2(node);
}

// bu fonksiyon dosya izinlerini kontrol edecek gerekirse
	// gerekli hata kodlarını ekrana basacak
// cat <main.c   main.c infile oluyor 
//infile olan dosyalar okunabilir mi bakacağız R_OK
// ls >deneme.txt gibi bir durumda yada append de (>>)
	// access kontrolüne gerek yok
// diğerlerini çalıştırılabilir mi diye bakacağız
		// printf("%s: Permission denied\n", filename);
		// printf("%s: No such file or directory\n", filename);