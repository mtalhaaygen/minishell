/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:07:53 by maygen            #+#    #+#             */
/*   Updated: 2023/07/31 17:48:47 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

s_minishell	gv;

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	s_env *env_list;
	env_list = fill_env(envp);
	//print_env_list(env_list);
	while (1)
	{
		char *line;
		Node *nodes;
		s_token *tokens;

		printf("talha@minishell");
		line = ft_readline("$ ");
		add_history(line);
		tokens = ft_tokens(line);
		nodes = ft_parser(tokens);
		/*********************/
		//printf("args[0] : %s\n", nodes->args[0]);
		ft_executor(nodes);
		/*********************/
		free(line);
	}
}