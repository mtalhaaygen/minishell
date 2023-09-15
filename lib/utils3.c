/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:29:13 by maygen            #+#    #+#             */
/*   Updated: 2023/09/15 18:42:34 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_find_redirection(t_node node)
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

int	find_full(char *new)
{
	int	size;
	int	len;

	if (!new)
		return (0);
	len = ft_strfind(new, '=');
	if (len == 0)
		len = ft_strlen(new);
	else
		len--;
	size = g_va->full_size - 1;
	while (size >= 0)
	{
		if (ft_strncmp(new, g_va->full[size], len) && \
				(new[len] == '=' || new[len] == '\0'))
			return (1);
		size--;
	}
	return (0);
}

int	file_access(char	*filename, int flag, int f2, t_node node)
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
		if (f2 == 7)
		{
			free(node.outfile->name);
			free(node.outfile);
		}
		else
		{
			free(node.infile->name);
			free(node.infile);
		}
		exit(1);
	}
	return (0);
}

void	add_dollar_question_mark(void)
{
	char	**new;
	char	*s;
	int		i;

	i = -1;
	s = ft_strdup("?=0");
	g_va->err_number = 0;
	g_va->full_size = arg_count(g_va->full) + 1;
	new = malloc(sizeof(char *) * g_va->full_size + 1);
	while (g_va->full[++i])
		new[i] = ft_strdup(g_va->full[i]);
	new[i++] = ft_strdup(s);
	new[i] = NULL;
	free(s);
	free(g_va->full);
	g_va->full = new;
}

int	ft_envadd_counter(void)
{
	int	count;

	count = g_va->env->env_count * 2;
	return (count);
}
