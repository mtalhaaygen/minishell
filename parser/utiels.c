#include "../minishell.h"
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
