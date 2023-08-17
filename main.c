/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:07:53 by maygen            #+#    #+#             */
/*   Updated: 2023/08/17 18:13:58 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

s_minishell	gv;
void	sigquit_handler(int sig)
{
	(void)sig;
	printf("Quit: 3\n");
}
void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\033[A", 3);
	ioctl(0, TIOCSTI, "\n");
}
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);

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
		free(line);
		nodes = ft_parser(tokens);
			
		int i = 0;
		while(tokens[i].value)
		{
    		free(tokens[i].value); 
    		i++;
		}
		free(tokens);
		/*int j = 0;
		while(j<gv.process_count)
		{
			i  = 0;
			while (i<nodes[j].arg_count)
			{
				free(nodes[j].args[i]);
				i++;
			}
			free(nodes[j].args);
			free(nodes[j].infile);
			free(nodes[j].outfile);
			
			j++;
		}
		
		free(nodes);*/
		//system("leaks minishell");		
		exec_start(nodes, envp);

	}
}