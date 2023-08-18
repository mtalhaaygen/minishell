/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:02:10 by maygen            #+#    #+#             */
/*   Updated: 2023/08/18 17:02:35 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
void	full_sort(s_env	*env_list) // a p q l t
{
	int	i;
	int	j;

	i = 0;
	while(env_list[i].full)
	{
		j = 0;
		while(env_list[j].full && env_list[j + 1].full)
		{
			if(!ft_strcmp(gv.env[j].full, gv.env[j + 1].full))
			{
				ft_swap(j);
			}
			//printf("i: %d j: %d\n", i, j);
			j++;
		}
		i++;
	}
}*/

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
	env_list = malloc (sizeof(s_env) * (len + 1));
	//gv.full = ft_calloc(1, sizeof(char *));
	env_list->env_count = len;
	while (i < len)
	{
		//gv.full[i] = ft_strdup(envp[i]);
		s = ft_split(envp[i], '=');
		env_list[i].key = ft_strdup(s[0]);
		env_list[i].value = ft_strdup(s[1]);
		free(s[0]);
		free(s[1]);
		free(s);
		i++;
		
	}
	//gv.full[i] = NULL;
	//full_sort(env_list);
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
