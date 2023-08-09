#include "../minishell.h"

// Optimized implementation of Bubble sort
void ft_swap(int j)
{
    char *tmp;
    tmp = ft_strdup(gv.env[j].full);
     //printf("tmp:%s - %s\n\n", tmp);
    gv.env[j].full = ft_strdup(gv.env[j+1].full);
     //printf("xp:%s - %s\n\n", xp, yp);
    gv.env[j+1].full= ft_strdup(tmp);
    //printf("yp:%s - %s\n\n", yp, tmp);
}
  
void  ft_print_array()
{
    int i;
    i = 0;
    while ( i < gv.env->env_count)
    {
        printf("%s \n", gv.env[i].full);
        i++;
    }
}
  
// Function to print an array
void ft_export()
{
    int i;
    int j;
    i = 0;

    while( i < gv.env->env_count - 1) 
    {
        j = 0;
        while(j < gv.env->env_count- 1 ) 
        {
            if(!ft_strcmp(gv.env[j].full, gv.env[j+1].full))
            {
                ft_swap(j);
            }
            //printf("i: %d j: %d\n", i, j);
            j++;
        }       
        i++;

    }
    ft_print_array();
}

  
// Function to print an array
/*
   int i;
    int j;
    int swapped;
    i = 0;
    while( i < gv.env->env_count - 2) 
    {

        swapped = 0;
        j = 0;
        while( j < gv.env->env_count - i - 2 ) 
        {
            if (gv.env[j].full > gv.env[j + 1].full) 
            {
                printf("%s\n",gv.env[j].full);
                ft_swap(gv.env[j].full, gv.env[j + 1].full);
                swapped = 1;
            }
            j++;
        }
        // If no two elements were swapped by inner loop,
        // then break
        if (swapped == 0)
            break;
        i++;
    }
    ft_print_array();
}
*/

/*
void ft_export(void)
{
    //char *tmp;
    int i;
    int j;

    i = 0;
    while(gv.env[i + 1].full)
    {
        j = 0;
        printf("*%s*\n",gv.env[i].full);

        while(gv.env[j + 1].full)
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
*/