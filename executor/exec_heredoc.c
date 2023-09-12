/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:55:02 by maygen            #+#    #+#             */
/*   Updated: 2023/09/12 15:51:31 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rm_heredoc(void)
{
	char	**args;
	int		i;

	i = 0;
	args = ft_calloc((3 + g_va->heredoc_count), sizeof(char *));
	args[0] = ft_strdup("/bin/rm");
	args[1] = ft_strdup("-rf");
	while (i < g_va->heredoc_count)
	{
		args[i + 2] = ft_strjoin("heredoc.txt", ft_itoa(i + 1));
		i++;
	}
	args[i + 2] = NULL;
	g_va->pid = fork();
	if (g_va->pid == 0)
		execve(args[0], args, NULL);
	else if (g_va->pid < 0) 
		return (perror("tsh: heredoc fork error"));
	free_pp(args);
}

void	node_change(t_node node, int i, int flag, char *txt)
{
	if (g_va->heredoc_count_node > 1)
		node.args[1] = ft_strdup(txt);
	if (flag == 1 && !ft_strcmp(node.args[0], "export") && !ft_strcmp(node.args[0], "echo") && !ft_strcmp(node.args[0], "ls") && !ft_strcmp(node.args[0], "cd"))
	{
		free(node.args[i]);
		node.args[i] = ft_strdup(txt);
		while (node.args[++i] && node.args[i + 1])
			node.args[i] = node.args[i + 1];
		node.args[i] = NULL;
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

// heredoc read
// readline ile promt yazdırılıp kullanıcıdan girdi beklenecek alınan 
// girdi str_join ile
// bir önceki satır ile birleştirilecek tabii arada bir \n de olacak
// herseferinde bir dosya açıp dosyanın içini sıfırlayıp full ü 
// dosyaya yazacağız
// Okuduğumuz tüm veriyi dosyaya yazıyoruz
// Burada direk ekrana basmak yerine heredocu execve ile
// çalıştıracağımız için node u güncelleyeceğiz
void	ft_executor_heredoc(t_node *nodes, int th, int i, int flag)
{
	char	*full;
	char	*txt;
	char	*buff;
	int		fd;

	g_va->heredoc_count++;
	g_va->heredoc_count_node++;
	buff = malloc (sizeof(char));
	buff[0] = '<';
	full = NULL;
	while (1)
	{
		buff = readline(" > ");
		buff = free_strjoin(buff, "\n");
		if (!(ft_strncmp(buff, nodes[th].args[i + 1], \
						ft_strlen(nodes[th].args[i + 1]))))
			full = free_strjoin(full, buff);
		else
			break ;
	}
	txt = ft_strjoin("heredoc.txt", ft_itoa(g_va->heredoc_count));
	fd = open(txt, O_TRUNC | O_CREAT | O_RDWR, 0777);
	ft_putstr_fd(full, fd);
	node_change(nodes[th], i, flag, txt);
}
