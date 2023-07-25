#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while(str[i])
		i++;
	return i;
}

char *ft_readline(char *str)
{
    char *buf;

    buf = readline(str);
    return (buf);
}

int my_isspace(char ch)
{
    if(ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == '\f' || ch == '\v')
        return (1);
    return (0);
}


