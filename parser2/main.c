#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    s_env *env_list;

    env_list = fill_env(envp);
    //print_env_list(env_list);
	while (1)
    {
        char *line;
        printf("talha@minishell");
        line = ft_readline("$"); 
        ft_tokens(line);
		
    }
}
