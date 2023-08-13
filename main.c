/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:07:53 by maygen            #+#    #+#             */
/*   Updated: 2023/08/09 11:45:03 by tdemir           ###   ########.fr       */
=======
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:07:53 by maygen            #+#    #+#             */
/*   Updated: 2023/08/10 16:50:54 by maygen           ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

s_minishell	gv;

<<<<<<< HEAD
int main(int argc, char **argv, char **envp)
=======
int	main(int argc, char **argv, char **envp)
>>>>>>> master
{
	(void)argc;
	(void)argv;

	s_env *env_list;

	env_list = fill_env(envp);
	gv.env = env_list;
	//ft_export();
	//print_env_list(env_list);
	while (1)
	{
		char *line;
		Node *nodes;
		s_token *tokens;
		line = ft_readline("$ ");
		add_history(line);

		tokens = ft_tokens(line);
		if(tokens[0].value)
		{
			nodes = ft_parser(tokens);
<<<<<<< HEAD
			//ft_executor(nodes, envp);
			exec_select(nodes, envp);
=======
			exec_start(nodes, envp);
>>>>>>> master
		}
		free(line);
	}
}
