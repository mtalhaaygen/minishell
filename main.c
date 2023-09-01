/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:07:53 by maygen            #+#    #+#             */
/*   Updated: 2023/09/01 18:24:08 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*g_va;

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
	t_env *env_list;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	g_va = malloc(sizeof(t_minishell));
	env_list = fill_env(envp);
	g_va->env = env_list;
	while (1)
	{
		char *line;
		Node *nodes;
		t_token *tokens;
		line = ft_readline("$ ");
		if (line[0])
			add_history(line);
		tokens = ft_tokens(line);
			

		free(line);
		if(tokens[0].value)
		{
			nodes = ft_parser(tokens);
			g_va->nodes = nodes;
			
		/*
			int j = 0;
			while(j<g_va->process_count)
			{
				int i  = 0;
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
		int i = -1;
		while(tokens[++i].value)
			free(tokens[i].value); 
		free(tokens);
	}
}
