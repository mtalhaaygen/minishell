/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:52:56 by maygen            #+#    #+#             */
/*   Updated: 2023/08/25 16:35:22 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_builtin(int status, Node node)
{
	if (status == ENV)
		print_env_list(g_va->env); //tüm env leri key value değerlerini kullanarak yazıyoruz
	else if (status == PWD)
		run_pwd();
	else if (status == ECHO)
		run_echo(node);
	else if (status == EXPORT)
		ft_export1(node);
	exit(0);
	// eğer eşittir yoksa sadece full e at, eğer eşittir değeri varsa hem full hemde key-value değerleri dolsun
}
void	run_other_builtin(int status, Node node)
{
	if (g_va->process_count > 1) // bu komutların pipe olduğu durumlarda çalışmaması için bu kokşul eklendi
		return ;
	if (status == CD)
		run_cd(node);
	else if (status == EXIT)
	{
		// free
		printf("exit\n");
		exit(0);
	}
	else if (status == UNSET)
		run_unset(node); // envsize - 1 kadar yer aç tüm envleri env_liste atarken gerekli değeri atlayarak devam et, silmek için yalnızca char *full değeri içerisinde değer olması yeterli
	else if (status == EXPORT)
		ft_export2(node);
}

int	is_builtin(char **args)
{
	if (ft_strcmp(args[0], "env"))
		return (ENV);
	if (ft_strcmp(args[0], "pwd"))
		return (PWD);
	if (ft_strcmp(args[0], "echo"))
		return (ECHO);
	if (ft_strcmp(args[0], "export") && args[1] == NULL) //çıktı verecek iken burda çalışmalı
		return (EXPORT);
	return (0);
}
int	is_other_builtin(Node node)
{
	if (ft_strcmp(node.args[0], "exit"))
		return (EXIT);
	if (ft_strcmp(node.args[0], "unset"))
		return (UNSET);
	if (ft_strcmp(node.args[0], "cd"))
		return (CD);
	if (ft_strcmp(node.args[0], "export") && node.args[1] != NULL) //çıktı vermeyecek iken burda çalışmalı
		return (EXPORT);
	return (0);
}
