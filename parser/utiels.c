#include "minishell.h"
/*
char* appendString(const char *dest, const char *src)
{
    // Hedef stringin boyutunu hesaplayalım

    size_t dest_size = strlen(dest);
    size_t src_size = strlen(src);

    // Bellekte hedef string için yeterli boyutta alan ayıralım
    char *result = (char *)malloc(dest_size + src_size + 1);


    // Bellek ayırma işlemi başarısız olduysa, NULL döndürelim
    if (!result) {
        printf("Bellek ayirma hatasi!\n");
        return NULL;
    }

    // Hedef stringin içeriğini kopyalayalım
    strcpy(result, dest);

    // Şimdi kaynak stringi hedefin sonuna kopyalayalım
    strcat(result, src);

    return result;
}
*/
char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;

	if (!s1 || !s2)
	{
		printf("!s1 || !s2\n\n");
		return (0);
	}
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

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
