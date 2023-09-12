/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:07:53 by maygen            #+#    #+#             */
/*   Updated: 2023/09/12 15:07:18 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*g_va;

void    sigquit_handler(int num)
{
    (void)num;
    if (g_va->s_back == 1)
    {
        write(1, "\033[2D", 4);
        write(1, "  ", 2);
        write(1, "\033[2D", 4);
        ioctl(0, TIOCSTI);
        g_va->s_back = 0;
    }
    g_va->s_back = 1;
}

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\033[A", 3);
	ioctl(0, TIOCSTI, "\n");
	g_va->syn_err = 1;
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;
	char	*line;
	t_node	*nodes;
	t_token	*tokens;

	(void)argc;
	(void)argv;
	g_va = malloc(sizeof(t_minishell));
	g_va->s_back = 0;
	
	env_list = fill_env(envp);
	g_va->env = env_list;
	add_dollar_question_mark();
	while (1)
	{
		g_va->syn_err = 0;
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, sigquit_handler);
		line = ft_readline("$ ");
		if (line[0])
			add_history(line);
		tokens = ft_tokens(line);
		free(line);
		if (tokens[0].value)
		{
			if (g_va->syn_err)
			{
				int x = -1;
				while(tokens[++x].value)
					free(tokens[x].value); 
				free(tokens);
				continue;
			}
			nodes = ft_parser(tokens);
			g_va->nodes = nodes;
			exec_start(nodes);
			int j = 0;
			while(j < g_va->process_count)
			{
				int i  = 0;
				while (i < nodes[j].arg_count)
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
			// infile name
			// outfile name
		}
		int i = -1;
		while(tokens[++i].value)
			free(tokens[i].value); 
		free(tokens);
	}
}
