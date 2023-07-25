#include "minishell.h"

char *ft_readline()
{
    char *buf;

    buf = readline("$");
    return (buf);
}