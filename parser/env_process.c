/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:06:43 by maygen            #+#    #+#             */
/*   Updated: 2023/07/31 17:27:24 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int env_counter(char **envp) //env'ye ekleme çıkarma yaparken sık sık kullanacağız
{
	int i;

	i = 0;
	while(envp[i] != NULL)
		i++;
	return (i);
}

s_env *fill_env(char **envp)
{
	s_env *env_list;
	char **s;
	int len;
	int i;

	i = 0;
	len = env_counter(envp);
	env_list = malloc(sizeof(s_env) * (len));
	while(i < len)
	{
		s = ft_split(envp[i],'=');
		env_list[i].key = ft_strdup(s[0]);
		env_list[i].value = ft_strdup(s[1]);
		i++;
	}
	return (env_list);
}

void print_env_list(s_env *env_list)
{
	int i;

	i = 0;
	while(env_list[i].key)
	{
		printf("%s=%s\n", env_list[i].key, env_list[i].value);
		i++;
	}
}

