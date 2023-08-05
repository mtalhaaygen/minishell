#include "../minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;
    char    x;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
        x = s[i];
		write(1, &x, fd);
		i++;
	}
}

int	ft_echo_param_checker(char *str)
{
	int	i;

	i = 2;
	if (!str[0] || str[0] != '-')
		return (0);
	if (!str[1] || str[1] != 'n')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	run_echo(Node node) //yalnızca stdinden girdi alıp stdouta yada yönlendirme ile dosyaya çıktı veren bir komut
{
	int	i;

	i = 1;
	if (node.args[i] == NULL)
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	while (ft_echo_param_checker(node.args[i]) == 1)
		i++;
	while (node.args[i])
	{
		ft_putstr_fd(node.args[i], 1);
		if (node.args[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (ft_echo_param_checker(node.args[1]) == 0)
		ft_putstr_fd("\n", 1);
}