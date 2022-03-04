/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:32:24 by rmonney           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/03/04 19:15:49 by rmonney          ###   ########.fr       */
=======
/*   Updated: 2022/03/04 19:04:17 by rmonney          ###   ########.fr       */
>>>>>>> d5620cbf97803f4be6b40d05bbc3645c2d788bcb
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
	char			*prompt;
	char			*current;
	int				cmd;
	int				s_quote;
	int				d_quote;
	char			**env_var;
	int				test_git;
}			t_para;

t_para	g_para;

int		search_fct(char *str);
void	do_fct(int cmd, char *current);
void	ft_echo(int mode, char *str);
int		ft_strstr(char *str, char *tofind);

#endif
