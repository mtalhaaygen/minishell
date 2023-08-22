/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:02:10 by maygen            #+#    #+#             */
/*   Updated: 2023/08/22 17:10:56 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_full(char **envp, int len)
{
	int	i;

	i = -1;
	g_va.full = ft_calloc(sizeof(char *) , (len + 1));
	if (!g_va.full)
		return ;
	while (++i < len)
		g_va.full[i] = envp[i];
	g_va.full[i] = NULL;
	g_va.full_size = i;
}
int	env_counter(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}

s_env	*fill_env(char **envp)
{
	s_env	*env_list;
	char	**s;
	int		len;
	int		i;

	i = 0;
	len = env_counter(envp);
	env_list = malloc(sizeof(s_env) * (len + 1));	
	env_list->env_count = len;
	while (i < len)
	{
		s = ft_split(envp[i], '=');
		env_list[i].key = ft_strdup(s[0]);
		env_list[i].value = ft_strdup(s[1]);
		free(s[0]);
		free(s[1]);
		free(s);
		i++;
	}
	fill_full(envp, len);
	return (env_list);
}

void	print_env_list(s_env *env_list)
{
	int	i;

	i = 0;
	while (env_list[i].key)
	{
		printf("%s=%s\n", env_list[i].key, env_list[i].value);
		i++;
	}
	exit(1);
}
