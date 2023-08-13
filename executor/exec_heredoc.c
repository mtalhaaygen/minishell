/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:29:36 by maygen            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/08/07 17:53:31 by maygen           ###   ########.fr       */
=======
/*   Updated: 2023/08/10 16:36:51 by maygen           ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

<<<<<<< HEAD
void	ft_executor_heredoc(Node *nodes,const int i)
=======
void	ft_executor_heredoc(Node *nodes, const int i)
>>>>>>> master
{
	// heredoc read
	// readline ile promt yazdırılıp kullanıcıdan girdi beklenecek alınan girdi str_join ile bir önceki satır ile birleştirilecek tabii arada bir \n de olacak
	char	*full;
	char	*buff;

	buff = malloc (sizeof(char));
	buff[0] = '<';
	full = NULL;
	while (1)
	{
		buff = readline(" > ");
		buff = free_strjoin(buff, "\n");
		if (!(ft_strncmp(buff, nodes[0].args[i + 1], ft_strlen(nodes[0].args[i + 1]))))
			full = free_strjoin(full, buff);
		else
			break;
	}
	// Okuduğumuz tüm veriyi STDOUT_FILENO (1)'e yazıyoruz
<<<<<<< HEAD
=======
	// Burada direk ekrana basmak yerine heredocu execve ile çalıştıralım
>>>>>>> master
	if (full)
		ft_putstr_fd(full, 1);
	else
		ft_putstr_fd(nodes[0].args[i + 1], 1);
}