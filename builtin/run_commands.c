/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 14:53:10 by maygen            #+#    #+#             */
/*   Updated: 2023/08/28 15:53:08 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_pwd(void)
{
	char	*s;

	s = getcwd(NULL, 0);
	if (!s)
		perror("tsh: pwd getcwd error");
	else
		printf("%s\n",s);
	free(s);
	exit(0);
}

void	run_cd(Node node)
{
	char	*s;

	if (node.arg_count != 1 && node.args[1][0] != '~')
	{
		if (chdir(node.args[1]) != 0)
			printf("tsh: cd: %s: No such file or directory\n", node.args[1]);
	}
	else
	{
		s = getenv("HOME");
		if (s && *s)
		{
			if (chdir(s))
				perror("tsh: cd chdir error");
		}
	}
}

void	del_env(int index)
{
	int		i;
	s_env	*nenv;

	i = -1;
	nenv = malloc(sizeof(s_env) * g_va->env->env_count);
	nenv->env_count = g_va->env->env_count - 1;
	while (g_va->env[++i].key)
	{
		if (i < index)
		{
			nenv[i].key = g_va->env[i].key;
			nenv[i].value = g_va->env[i].value;
		}
		if (i > index)
		{
			nenv[i - 1].key = g_va->env[i].key;
			nenv[i - 1].value = g_va->env[i].value;
		}
	}
	nenv[i - 1].key = NULL;
	nenv[i - 1].value = NULL;
	g_va->env = nenv;
}

void	del_full(int index)
{
	char	**new;
	int		i;

	i = -1;
	g_va->full_size = g_va->full_size - 1;
	new = malloc(sizeof(char *) * g_va->full_size + 1);
	while (g_va->full[++i])
	{
		if (i < index)
			new[i] = ft_strdup(g_va->full[i]);
		if (i > index)
			new[i - 1] = ft_strdup(g_va->full[i]);
	}
	new[i - 1] = NULL;
	g_va->full = new;
}

void	run_unset(Node node)
{
	int	i;
	int	size;
	int	len;

	if (node.arg_count > 1)
	{
		i = 0;
		while (node.args[++i])
		{
			len = ft_strlen(node.args[i]);
			size = g_va->env->env_count - 1;
			while (size > 0)
			{
				if (ft_strcmp(node.args[i], g_va->env[size].key))
				{
					del_env(size);
					break ;
				}
				size--;
			}
			size = g_va->full_size;
			while (size > 0)
			{
				if (ft_strncmp(node.args[i], g_va->full[size], len) && \
							(node.args[i][len] == '=' || node.args[i][len] == '\0'))
					del_full(size);
				size--;
			}
		}
	}
}
