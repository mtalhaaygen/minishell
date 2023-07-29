/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:07:53 by maygen            #+#    #+#             */
/*   Updated: 2023/07/28 20:07:54 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	s_env *env_list;
	env_list = fill_env(envp);
	print_env_list(env_list);
	while (1)
	{
		char *line;
		Node *nodes;
		s_token *tokens;

		printf("talha@minishell");
		line = ft_readline("$ ");
		ft_history(line); // linuxda hata veriyor olabilir
		tokens = ft_tokens(line);
		nodes = ft_parser(tokens);
		/*********************/
		ft_executor(nodes);
		/*********************/
		free(line);
	}
}
