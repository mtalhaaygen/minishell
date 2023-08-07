#include "../minishell.h"


char *ft_dolkey(s_token *tokens,int i, int j)
{
    char *dolkey;
    int len;
    int tmp;
    int k; 
    j++;

    len = 0;
    k = 0;
    tmp = j;
    while(tokens[i].value[tmp])
    {
        tmp++;
        len++;
    }
    dolkey = ft_calloc(len,sizeof(char));
    while(tokens[i].value[j])
    {
       dolkey[k] = tokens[i].value[j];
       k++;
       j++;
    }
    dolkey[k] = '\0';
    return (dolkey);
}

char *ft_dolval(char *dolkey)
{
    int i;

    i = 0;
    while (gv.env[i].key)
    {
        if(ft_strcmp(dolkey, gv.env[i].key))
            return (gv.env[i].value);
        i++;
    }
    return (NULL);
}
char *ft_change_token(char *dolval, s_token *tokens, int i, int j)
{
    int len;
    char *str;
    int k;
    int s;
    len = 0;
    s = 0;
    k = 0;
    while(tokens[i].value[len] != '$')
        len++;
    len += ft_strlen(dolval);
    str = ft_calloc(len,sizeof(char));
    while(k < j)
    {
        str[k] = tokens[i].value[k];
        k++;
    }
    while(dolval[s])
    {
        str[k] = dolval[s];
        k++;
        s++;
    }
    str[k] = '\0';
    return (str);
}
s_token *ft_dollar(s_token *tokens)
{
    int i;
    int j;

    i = 0;
    char *dolkey;
    char *dolval;
    while(tokens[i].value)
    {
        j = 0;
        while(tokens[i].value[j] != '\0')
        {
            if(tokens[i].value[j] == '$')
            {
                dolkey = ft_strdup(ft_dolkey(tokens, i,j));
                dolval = ft_strdup(ft_dolval(dolkey));
                tokens[i].value = ft_strdup(ft_change_token(dolval, tokens, i,j));
                //printf("%s\n",tokens[i].value);
            }            
            j++;
        }
        i++;
    }
    return (tokens);
}