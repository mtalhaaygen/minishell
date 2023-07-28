#include "minishell.h"
#include <fcntl.h>

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	int fd;
	CHECK(fd = open("olmayandosya.txt", O_RDWR));
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
		//add_history(line);
		tokens = ft_tokens(line);

		ft_parser(tokens);
		//free(line);
	}
}
