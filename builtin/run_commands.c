#include "../minishell.h"

void	run_pwd(void)
{
	char *s;

	s = getcwd(NULL, 0);
	if (!s)
		perror("pwd getcwd error ");
	else
		printf("%s\n",s);
	free(s);
}

void	run_cd(Node node)
{
	char	*s;

	if (node.arg_count != 1)
	{
		if (chdir(node.args[1]) != 0)
			perror("cd error ");
	}
	else
	{
		s = getenv("HOME");
		if (s && *s)
		{
			if (chdir(s))
				perror("chdir error ");
		}
	}
}
