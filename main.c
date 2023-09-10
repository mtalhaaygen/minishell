/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:07:53 by maygen            #+#    #+#             */
/*   Updated: 2023/09/10 16:33:26 by tdemir           ###   ########.fr       */
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
	t_env	*env_list;
	char	*line;
	t_node	*nodes;
	t_token	*tokens;

	(void)argc;
	(void)argv;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	g_va = malloc(sizeof(t_minishell));
	env_list = fill_env(envp);
	g_va->env = env_list;
	while (1)
	{
		line = ft_readline("$ ");
		if (line[0])
			add_history(line);
		tokens = ft_tokens(line);
		free(line);
		if (tokens[0].value)
		{
			if (g_va->syn_err)
				continue;
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
			
			free(nodes);
*/
			exec_start(nodes);
		}
		int i = -1;
		while(tokens[++i].value)
			free(tokens[i].value); 
		free(tokens);
	}
}
