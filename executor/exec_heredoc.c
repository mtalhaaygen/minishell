/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:29:36 by maygen            #+#    #+#             */
/*   Updated: 2023/08/09 18:17:14 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_executor_heredoc(Node *nodes, const int i) // i heredoc'un indexini tutuyor
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
	// Burada ft_executor a gönderece
	if (full)
		ft_putstr_fd(full, 1);
	else
		ft_putstr_fd(nodes[0].args[i + 1], 1);
}