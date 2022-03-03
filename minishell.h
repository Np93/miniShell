/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:32:24 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/03 21:06:33 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stddef.h>
# include <signal.h>
# include <string.h>
# include <curses.h>
# include <term.h>
# include <dirent.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <sys/stat.h>

typedef struct s_para {
	char	*prompt;
	char	*current;
	int		cmd;
}			t_para;

t_para	g_para;

int		search_fct(char *str);
void	do_fct(int cmd, char *current);
void	ft_echo(int mode, char *str);

#endif
