/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_with_ioctl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 12:48:50 by maygen            #+#    #+#             */
/*   Updated: 2023/07/25 19:06:26 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include "minishell.h"
// buna en son bakacağız
void sigint_handler(int signum)
{
    printf("SIGINT alındı, kapatılıyor...\n");
    exit(0);
}

void sigquit_handler(int signum)
{
    printf("SIGQUIT alındı, sonlandırılıyor...\n");
    exit(3);
}

int set_ctrl(void)
{
	struct termios term;
	int fd = STDIN_FILENO; // STDIN_FILENO, standart giriş (stdin) dosya tanımlayıcısıdır
	// Terminal ayarlarını al
	if (ioctl(fd, TIOCGETA, &term) == -1)
	{
		perror("ioctl");
		return (1);
	}

	term.c_cc[VINTR] = '\n'; // ctrl-C için yeni satır karakteri
	term.c_cc[VEOF] = '\x04'; // ctrl-D için ASCII 4 (End of Transmission, EOT) karakteri
	term.c_cc[VQUIT] = 0; // VQUIT, ctrl-\ için karakter sabiti :D
	// Değiştirilmiş ayarları aygıta uygula
	if (ioctl(fd, TIOCSETA, &term) == -1)
	{
		perror("ioctl");
		return (1);
	}
	else
		return (0);
}*/