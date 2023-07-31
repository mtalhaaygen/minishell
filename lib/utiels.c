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
void	*ft_memset(void *src, int c, size_t len)
{
	size_t	i;
	char	*src1;

	i = 0;
	src1 = (char *)src;
	if (!src && !len)
		return (NULL);
	while (i < len)
	{
		src1[i] = c;
		i++;
	}
	return (src);
}


void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
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
