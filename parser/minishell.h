#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef  struct t_env
{
    char *key;
    char *value;
}   s_env;

s_env *fill_env(char **envp);
char	**ft_split(char const *s, char c);
void print_env_list(s_env *env_list);
char *ft_readline();
char	*ft_strdup(char *src);
#endif