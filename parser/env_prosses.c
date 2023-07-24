#include "minishell.h"

s_env *fill_env(char **envp)
{
    s_env *env_list;
    char **s;
    env_list = malloc(sizeof(env_list));

    int i = 0;
    while(*envp != NULL)
    {
        s = ft_split(*envp,'=');
        env_list[i].key = s[0];
        env_list[i].value = s[1];
        envp++;
        i++;
    }
    env_list[i].key = NULL;
    env_list[i].value = NULL;
    return (env_list);
}   

void print_env_list(s_env *env_list)
{
    int i;

    i = 0;
    while(env_list[i].key)
    {
        printf("%s=%s\n", env_list[i].key, env_list[i].value);
        i++;
    }
}
