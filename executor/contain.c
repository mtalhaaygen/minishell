/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:21:27 by maygen            #+#    #+#             */
/*   Updated: 2023/09/14 17:43:12 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	question_mark_update(char *new_value, int x)
{
	full_update(new_value);
	env_update(new_value);
	free(new_value);
	g_va->err_number = x;
}
