/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:52:56 by maygen            #+#    #+#             */
/*   Updated: 2023/08/17 19:52:24 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_builtin(int status, Node node)
{
	if (status == ENV)
		print_env_list(gv.env); //tüm env leri key value değerlerini kullanarak yazıyoruz
	else if (status == PWD)
		run_pwd();
	else if (status == ECHO)
		run_echo(node);
	else if (status == EXPORT) // eğer eşittir yoksa sadece full e at, eğer eşittir değeri varsa hem full hemde key-value değerleri dolsun
		//ft_export();
	exit(1);
}
void	run_other_builtin(int status, Node node)
{
	if (status == CD)
		run_cd(node);
	else if (status == EXIT)
	{
		// free
		exit(1);
	}
	else if (status == UNSET)
		printf("unset çalıştır\n"); // envsize - 1 kadar yer aç tüm envleri env_liste atarken gerekli değeri atlayarak devam et, silmek için yalnızca char *full değeri içerisinde değer olması yeterli
}

int	is_builtin(char *command)
{
	if (ft_strcmp(command, "env"))
		return (ENV);
	if (ft_strcmp(command, "pwd"))
		return (PWD);
	if (ft_strcmp(command, "echo"))
		return (ECHO);
	if (ft_strcmp(command, "export"))
		return (EXPORT);
	return (0);
}
int	is_other_builtin(char *command)
{
	if (ft_strcmp(command, "exit"))
		return (EXIT);
	if (ft_strcmp(command, "unset"))
		return (UNSET);
	if (ft_strcmp(command, "cd"))
		return (CD);
	return (0);
}
