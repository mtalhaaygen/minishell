#include "../minishell.h"

void	run_pwd(void)
{
	char *s;

	s = getcwd(NULL, 0);
	if (!s)
		perror("hata");
	else
		printf("%s\n",s);
	free(s);
}