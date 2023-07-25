#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    s_env *env_list;

    env_list = fill_env(envp);
    int i;

    i = 0;
    while(env_list[i].key)
    {
        printf("%s=%s\n", env_list[i].key, env_list[i].value);
        i++;
    }
    //print_env_list(env_list);
 
}
