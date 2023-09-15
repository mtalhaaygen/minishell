/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:21:27 by maygen            #+#    #+#             */
/*   Updated: 2023/09/15 17:07:30 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	question_mark_update(char *new_value, int x)
{
	full_update(new_value);
	env_update(new_value);
	free(new_value);
	g_va->err_number = x;
}

char	*ft_heredoc_file(char *full)
{
	int		fd;
	char	*co;
	char	*txt;

	co = ft_itoa(g_va->heredoc_count);
	txt = ft_strjoin("heredoc.txt", co);
	free(co);
	fd = open(txt, O_TRUNC | O_CREAT | O_RDWR, 0777);
	ft_putstr_fd(full, fd);
	free(full);
	return (txt);
}

int	ft_find_heredoc(t_node *nodes, int flag, int th, int i)
{
	int	status;

	if (flag > 1)
		i = i - 1;
	status = ft_strcmp("<<", nodes[th].args[i]);
	if (status == 1 && nodes[th].args[i + 1])
	{
		flag++;
		ft_executor_heredoc(nodes, th, i, flag);
	}
	return (status);
}
