/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:57:34 by maygen            #+#    #+#             */
/*   Updated: 2023/09/15 18:13:37 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_child_process(t_node *nodes, int i)
{
	int		status;
	char	*bin_command;

	status = is_other_builtin(nodes[i]);
	if (nodes[i].args[0] && !status)
	{
		g_va->pid = fork();
		if (g_va->pid == 0)
		{
			ft_process_merge(i);
			is_redirection(nodes, i);
			status = is_builtin(nodes[i].args);
			if (status)
				run_builtin(status, nodes[i]);
			bin_command = ft_access(nodes[i].args[0]);
			if (execve(bin_command, nodes[i].args, g_va->full))
				ft_perror(bin_command);
			exit (127);
		}
		else if (g_va->pid < 0)
			return (perror("tsh: executor fork error"));
	}
	run_other_builtin(status, nodes[i]);
}

void	ft_executor(t_node *nodes)
{
	int		status;
	int		i;
	char	*er;

	i = -1;
	while (++i < g_va->process_count)
		ft_child_process(nodes, i);
	pipe_close();
	i = -1;
	status = -1;
	while (++i < g_va->process_count)
		waitpid(g_va->pid, &status, 0);
	if (WIFEXITED(status) && g_va->err_number >= 0)
	{
		g_va->err_number = WEXITSTATUS(status);
		er = ft_itoa(g_va->err_number);
		question_mark_update(ft_strjoin("?=", er), g_va->err_number);
		free(er);
		rm_heredoc();
	}
}

void	exec_start(t_node *nodes)
{
	t_process	*process;
	int			i;

	if (!g_va->nodes[g_va->process_count - 1].args[0])
		g_va->process_count -= 1;
	if (g_va->process_count > 1)
	{
		process = ft_calloc(g_va->process_count - 1, sizeof(t_process));
		if (!process)
			return ;
		i = -1;
		while (++i < g_va->process_count - 1)
		{
			if (pipe(process[i].fd) == -1)
				perror("tsh: pipe not created");
		}
		g_va->process = process;
	}
	exec_select(nodes);
}

void	exec_select(t_node *nodes)
{
	int		i;
	int		th;
	int		flag;

	th = -1;
	g_va->heredoc_count = 0;
	while (++th < g_va->process_count)
	{
		i = -1;
		flag = 0;
		g_va->heredoc_count_node = 0;
		if (ft_strcmp("<<", nodes[th].args[0]) && nodes[th].args[1] == NULL)
			break ;
		while (nodes[th].args[++i] != NULL && nodes[th].args[i])
		{
			if (ft_find_heredoc(nodes, flag, th, i) == -1)
				break ;
		}
	}
	ft_executor(nodes);
}
