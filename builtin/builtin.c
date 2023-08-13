/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:52:56 by maygen            #+#    #+#             */
/*   Updated: 2023/08/06 18:09:54 by maygen           ###   ########.fr       */
=======
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:52:56 by maygen            #+#    #+#             */
/*   Updated: 2023/08/09 16:34:42 by tdemir           ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_builtin(int status, Node node)
{
	if (status == CD)
		run_cd(node);
	else if (status == ENV)
		print_env_list(gv.env); //tüm env leri key value değerlerini kullanarak yazıyoruz
	else if (status == PWD)
		run_pwd();
	else if (status == EXIT)
	{
		// free
		exit(1);
	}
	else if (status == ECHO)
		run_echo(node);
	else if (status == UNSET)
		printf("unset çalıştır\n"); // envsize - 1 kadar yer aç tüm envleri env_liste atarken gerekli değeri atlayarak devam et, silmek için yalnızca char *full değeri içerisinde değer olması yeterli
	else if (status == EXPORT) // eğer eşittir yoksa sadece full e at, eğer eşittir değeri varsa hem full hemde key-value değerleri dolsun
<<<<<<< HEAD
		printf("export çalıştır\n");
=======
		ft_export();
>>>>>>> master
	else
		printf("command not builtin\n");
}

int	is_builtin(char *command)
{
	if (ft_strcmp(command, "cd"))
		return (CD);
	if (ft_strcmp(command, "env"))
		return (ENV);
	if (ft_strcmp(command, "pwd"))
		return (PWD);
	if (ft_strcmp(command, "exit"))
		return (EXIT);
	if (ft_strcmp(command, "echo"))
		return (ECHO);
	if (ft_strcmp(command, "unset"))
		return (UNSET);
	if (ft_strcmp(command, "export"))
		return (EXPORT);
	return (0);
}
