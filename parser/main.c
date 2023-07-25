#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	s_env *env_list;
	env_list = fill_env(envp);
	//print_env_list(env_list);
	while (1)
	{
		char *line;
		Node *nodes;

		printf("talha@minishell");
		line = ft_readline("$ ");
		add_history(line);
		ft_tokens(line);

		//nodes = parser(line);
		free(line);
	}
}
