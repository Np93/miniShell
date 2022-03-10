/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:32:24 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/09 23:51:13 by rmonney          ###   ########.fr       */
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
	char			*out;
	int				cmd;
	char			**argv;
	char			**env;
}			t_para;

typedef struct s_parse {
	char	*str;
	char	*tmp;
	int		i;
	int		j;
	int		k;
}			t_parse;

int		search_fct(char *str);
void	do_fct(int cmd, t_para *para);
void	ft_echo(int mode, char *str);
int		ft_strstr(char *str, char *tofind);
int		ft_strlen(char *str);
char	*ft_strdup(const char *s1);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
void	ft_env(char **env);
void	ft_pwd(t_para *para);
int		ft_export(t_para *para);
int		ft_unset(t_para *para);
void	ft_unset2(t_para *para, char *arg);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*prompt_init(int argc, char **argv);
char	*current_parser(t_para *para);
void	current_parser2(t_para *para, t_parse *p);
int		current_parser3(t_para *para, t_parse *p);
int		current_parser4(t_para *para, t_parse *p);
char	*get_dollar(char *current, int i, t_para *para);
void	error_handler(int error);
char	*ft_getenv(t_para *para, char *var);
void	ft_cd(t_para *para, int cmd);

#endif
