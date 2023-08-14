/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:29:36 by maygen            #+#    #+#             */
/*   Updated: 2023/08/14 23:54:01 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_executor_heredoc(Node *nodes, const int th, const int i)
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
		if (!(ft_strncmp(buff, nodes[th].args[i + 1], ft_strlen(nodes[th].args[i + 1]))))
			full = free_strjoin(full, buff);
		else
			break;
	}
	// herseferinde bir dosya açıp dosyanın içini sıfırlayıp full ü dosyaya yazacağız
	fd = open("heredoc.txt", O_TRUNC | O_CREAT | O_RDWR, 0777);
	// Okuduğumuz tüm veriyi dosyaya yazıyoruz
	if (full)
		ft_putstr_fd(full, fd);
	else
		ft_putstr_fd(nodes[th].args[i + 1], fd);

	// Burada direk ekrana basmak yerine heredocu execve ile çalıştıracağımız için node u güncelleyeceğiz
	// node_change(nodes[th], i); // 
}