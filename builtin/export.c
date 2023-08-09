#include "../minishell.h"


void ft_export(void)
{
    char *tmp;
    int i;
    int j;

    i = 0;
    while(gv.env[i].full)
    {
        j = 0;
        while(gv.env[j].full)
        {
            if(ft_strcmp(gv.env[j].full, gv.env[j+1].full))
            {
                tmp = ft_strdup(gv.env[j].full);
                free(gv.env[i].full);
                gv.env[i].full = ft_strdup(gv.env[i+1].full);
                free(gv.env[i+1].full);
                gv.env[i+1].full = ft_strdup(gv.env[i].full);
            }
            j++;
        }
        i++;
    }
    i =0;
    while(gv.env[i].full)
    {
        printf("%s\n", gv.env[i].full);
        i++;
    }
}