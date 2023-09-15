/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:47:28 by maygen            #+#    #+#             */
/*   Updated: 2023/09/15 17:42:15 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_perror(const char *str)
{
	write(1, "tsh: ", 6);
	perror(str);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;
	char	x;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		x = s[i];
		write(fd, &x, 1);
		i++;
	}
}

int	ft_strfind(char	*str, int c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i + 1);
	return (0);
}

void	ft_o(t_node node, int i, t_token *tokens)
{
	node.infile->type = TOKEN_O;
	node.infile->name = tokens[i + 1].value;
}

void	ft_free_node(t_node	*nodes)
{
	int	j;
	int	i;

	j = 0;
	while (j < g_va->process_count)
	{
		i = 0;
		while (i < nodes[j].arg_count)
		{
			free(nodes[j].args[i]);
			i++;
		}
		free(nodes[j].args);
		free(nodes[j].infile);
		free(nodes[j].outfile);
		j++;
	}
	free(nodes);
}
