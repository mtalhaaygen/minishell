/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:55:02 by maygen            #+#    #+#             */
/*   Updated: 2023/08/26 16:02:37 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rm_heredoc()
{
	char **args;

	args = ft_calloc(4, sizeof(char *));
	args[0] = ft_strdup("/bin/rm");
	args[1] = ft_strdup("-rf");
	args[2] = ft_strdup("heredoc.txt");
	args[3] = NULL;
	g_va->pid = fork();
	if (g_va->pid == 0)
		execve(args[0], args, NULL);
	else if (g_va->pid < 0) 
		return (perror("tsh: heredoc fork error"));
	free_pp(args);
}

void	node_change(Node node, int i, int flag)
{
	if (flag == 1)
	{
		if (!ft_strcmp(node.args[0], "export"))
		{
			free(node.args[i]);
			node.args[i] = ft_strdup("heredoc.txt");
			while (node.args[++i] && node.args[i + 1])
				node.args[i] = node.args[i + 1];
			node.args[i] = NULL;
		}
		else
		{
			node.args[1] = NULL;
			node.args[2] = NULL;
		}
	}
	else
	{
		if (node.args[i][0] == '<' && node.args[i][1] == '<')
		{
			while (node.args[i] && node.args[i + 2])
			{
				node.args[i] = node.args[i + 2];
				i++;
			}
			while (node.args[i])
				node.args[i] = NULL;
		}
	}
}

void	ft_executor_heredoc(Node *nodes, const int th, const int i, int flag)
{
	// heredoc read
	// readline ile promt yazdırılıp kullanıcıdan girdi beklenecek alınan girdi str_join ile bir önceki satır ile birleştirilecek tabii arada bir \n de olacak
	char	*full;
	char	*buff;
	int		fd;

	buff = malloc (sizeof(char));
	buff[0] = '<';
	full = NULL;
	while (1)
	{
		buff = readline(" > ");
		buff = free_strjoin(buff, "\n");
		if (!(ft_strncmp(buff, nodes[th].args[i + 1], ft_strlen(nodes[th].args[i + 1])))) // 
			full = free_strjoin(full, buff);
		else
			break;
	}
	// herseferinde bir dosya açıp dosyanın içini sıfırlayıp full ü dosyaya yazacağız
	fd = open("heredoc.txt", O_TRUNC | O_CREAT | O_RDWR, 0777);
	// Okuduğumuz tüm veriyi dosyaya yazıyoruz
	ft_putstr_fd(full, fd);
	// Burada direk ekrana basmak yerine heredocu execve ile çalıştıracağımız için node u güncelleyeceğiz
	node_change(nodes[th], i, flag);
}