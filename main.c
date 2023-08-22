/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:07:53 by maygen            #+#    #+#             */
/*   Updated: 2023/08/22 18:11:07 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	s_env *env_list;

	g_va = malloc(sizeof(s_minishell));
	env_list = fill_env(envp);
	g_va->env = env_list;
	signal(SIGINT, sigint_handler);
	while (1)
	{
		char *line;
		//Node *nodes;
		s_token *tokens;
		line = ft_readline("$ ");
		if(!line)
		{
			write(1, "\033[D", 3);
			write(1, "\033[D", 3);
			printf("exit\n");
			exit(1);	
		}
		if (line[0])
			add_history(line);

		tokens = ft_tokens(line);
		free(line);
		if(tokens[0].value)
		{
			//nodes = ft_parser(tokens);
			//g_va->nodes = nodes;
			
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
			//exec_start(nodes, envp);
		}
		int i = 0;
		while(tokens[i].value)
		{
			free(tokens[i].value); 
			i++;
		}
		free(tokens);
		

	}
}
