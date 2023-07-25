#include "minishell.h"

s_env *fill_env(char **envp)
{
    s_env *env_list;
    char **s;
    int len;

    len = 0;
    while(envp[len] != NULL)
    {
        len++;
    }
    env_list = malloc(sizeof(s_env) * (len));

    int i = 0;
    while(i < len)
    {
        s = ft_split(envp[i],'=');
        env_list[i].key = ft_strdup(s[0]);
        env_list[i].value = ft_strdup(s[1]);
        i++;
    }
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
