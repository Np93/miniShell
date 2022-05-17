/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:30:45 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/17 21:03:46 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGUSR1, sig_handler);
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (g_glob.main == 8)
			exit(0);
		if (g_glob.main == 1)
		{
			rl_replace_line("", 0);
			write(1, "\n", 1);
			rl_on_new_line();
			rl_redisplay();
		}
	}
	else if (sig == SIGUSR1)
		g_glob.exit_status = 1;
}
