/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:07:53 by maygen            #+#    #+#             */
/*   Updated: 2023/09/14 19:27:37 by maygen           ###   ########.fr       */
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

void	minishell_init(int argc, char **argv,char **envp)
{
	t_env	*env_list;
	
	(void)argc;
	(void)argv;
	g_va = malloc(sizeof(t_minishell));
	g_va->s_back = 0;
	env_list = fill_env(envp);
	g_va->env = env_list;
	add_dollar_question_mark();
}
t_token	*ft_main_sep()
{
	char	*line;
	t_token	*tokens;

	g_va->syn_err = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	line = ft_readline("$ ");
	if (line[0])
		add_history(line);
	tokens = ft_tokens(line);
	free(line);
	return (tokens);
}

int	main(int argc, char **argv, char **envp)
{
	t_node	*nodes;
	t_token	*tokens;

	minishell_init(argc, argv, envp);
	while (1)
	{
		tokens = ft_main_sep();
		if (tokens[0].value)
		{
			if (g_va->syn_err)
			{
				ft_free_token(tokens);
				continue;
			}
			nodes = ft_parser(tokens);
			g_va->nodes = nodes;
			exec_start(nodes);
			ft_free_node(nodes);
		}
		ft_free_token(tokens);
	}
}
