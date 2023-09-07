/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:52:56 by maygen            #+#    #+#             */
/*   Updated: 2023/09/07 19:30:19 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_builtin(int status, t_node node)
{
	if (status == ENV)
		print_env_list(g_va->env);
	else if (status == PWD)
		run_pwd();
	else if (status == ECHO)
		run_echo(node);
	else if (status == EXPORT)
		ft_export1(node);
	exit(0);
}

	// bu komutların pipe olduğu durumlarda çalışmaması için bu kokşul eklendi
	// exit de free
void	run_other_builtin(int status, t_node node)
{
	if (g_va->process_count > 1)
		return ;
	if (status == CD)
		run_cd(node);
	else if (status == EXIT)
		run_exit(node);
	else if (status == UNSET)
		run_unset(node);
	else if (status == EXPORT)
		ft_export2(node);
}

int	is_builtin(char **args)
{
	if (ft_strcmp(args[0], "env"))
		return (ENV);
	if (ft_strcmp(args[0], "pwd"))
		return (PWD);
	if (ft_strcmp(args[0], "echo"))
		return (ECHO);
	if (ft_strcmp(args[0], "export") && args[1] == NULL)
		return (EXPORT);
	return (0);
}

int	is_other_builtin(t_node node)
{
	if (ft_strcmp(node.args[0], "exit"))
		return (EXIT);
	if (ft_strcmp(node.args[0], "unset"))
		return (UNSET);
	if (ft_strcmp(node.args[0], "cd"))
		return (CD);
	if (ft_strcmp(node.args[0], "export") && (node.args[1] != NULL \
			&& node.args[1][0] != '<' && node.args[1][0] != '>') \
					&& (node.args[1][0] != '<' && node.args[1][1] != '<'))
		return (EXPORT);
	return (0);
}

	// if (node.args[1] == NULL) 
	// command : export, command : export | grep a, parametresiz
	// printf("deneme\n");
void	ft_export1(t_node node)
{
	(void)node;
	ft_print_full(g_va->full);
	exit(0);
}
