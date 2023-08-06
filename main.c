/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:07:53 by maygen            #+#    #+#             */
/*   Updated: 2023/08/06 13:11:17 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

s_minishell	gv;

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	s_env *env_list;
	env_list = fill_env(envp);
	gv.env = env_list;
	// print_env_list(env_list);
	while (1)
	{
		char *line;
		Node *nodes;
		s_token *tokens;

		line = ft_readline("$ ");
		add_history(line);
		tokens = ft_tokens(line);
		nodes = ft_parser(tokens);
		ft_executor(nodes, envp);
		free(line);
	}
}
