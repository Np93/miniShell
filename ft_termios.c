/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termios.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:13:06 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/19 16:04:02 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_termios(t_para *para)
{
	int	fd;

	fd = STDIN_FILENO;
	if (!isatty(fd))
		error_handler(5, para);
	if (tcgetattr(fd, &para->term) != 0)
		error_handler(6, para);
	para->term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(fd, TCSANOW, &para->term) != 0)
		error_handler(6, para);
}
