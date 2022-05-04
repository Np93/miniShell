/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:32:24 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/04 20:10:46 by rmonney          ###   ########.fr       */
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
# include <errno.h>

typedef struct s_para {
	char			*prompt;
	char			*current;
	char			*out;
	char			*bait;
	int				cmd;
	char			**argv;
	char			**env;
	char			**split_redi;
	struct termios	term;
}			t_para;

typedef struct s_parse {
	char	*str;
	char	*tmp;
	int		i;
	int		j;
	int		k;
}			t_parse;

typedef struct s_glob {
	int		exit_status;
	int		main;
}			t_glob;

t_glob	g_glob;

# define STDIN STDIN_FILENO
# define STDOUT STDOUT_FILENO

int		search_fct(char *str);
void	do_fct(int cmd, t_para *para);
void	cmd_not_found(char *str);
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
char	*ft_strjoin2(char *s1, char *s2);
char	*prompt_init(int argc, char **argv);
int		current_parser(t_para *para);
void	current_parser2(t_para *para, t_parse *p);
int		current_parser3(t_para *para, t_parse *p);
int		current_parser4(t_para *para, t_parse *p);
int		current_parser5(t_para *para, t_parse *p);
int		current_parser6(t_para *para, t_parse *p);
void	current_parser7(t_para *para, t_parse *p);
int		current_parser8(int err, t_para *para);
char	*get_dollar(char *current, int i, t_para *para);
void	error_handler(int error, t_para *para);
char	*ft_getenv(t_para *para, char *var);
void	ft_cd(t_para *para);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*get_env(char **env, char *envi);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	rl_replace_line(const char *s, int i);
void	cmd_not_found(char *str);
void	cmd_not_found2(char *str);
int		verif_fquote(t_para *para, char *str);
int		cmd_cmp(char *str);
void	ft_signal(void);
void	sig_handler(int sig);
int		ft_execve(t_para *para);
char	**all_path_exec(t_para *para, char *end);
void	free_exec(char **argv, char **path);
int		exec_and_return(char **all_path, char **argv, t_para *para);
void	ft_check_path(char **argv);
char	*last_path(char *arg);
void	welcome(void);
void	welcome1(void);
void	welcome2(void);
void	welcome3(void);
void	welcome4(void);
void	welcome5(void);
void	welcome6(void);
void	welcome7(void);
void	welcome8(void);
void	welcome9(void);
void	welcome10(void);
void	ft_termios(t_para *para);
int		ft_atoi(char *str);
char	*ft_itoa(int n);
void	ft_readline(t_para *para);
void	ft_readline2(t_para *para);
int		search_redirect(t_para *para);
int		search_redirect2(char *str, int i);
int		search_redirect3(t_para *para, int i);
void	launch_redi(t_para *para);
void	launch_redi1(t_para *para);
void	launch_redi2(t_para *para);
char	*cpy_bf_redi(char *str, int i);
char	*int_to_str_redi(int code);
char	*unquoter(char *str, t_para *para);
void	unquoter2(t_para *para, t_parse *p, char *str);
int		unquoter3(t_para *para, t_parse *p, char *str);
int		unquoter4(t_para *para, t_parse *p, char *str);
int		unquoter5(t_parse *p, char *str);
int		unquoter6(t_para *para, t_parse *p, char *str);
void	unquoter7(t_parse *p, char *str);
char	*grep_spec(char *str, t_para *para, int mod);
void	grep_spec1(t_parse *p);
void	grep_spec2(t_parse *p, char *str);
void	grep_spec3(t_para *para, t_parse *p, char *str);
void	grep_spec4(t_para *para, t_parse *p, char *str);
void	grep_spec5(t_para *para, t_parse *p, char *str);
int		grepxec(t_para *para);
int		grepr(t_para *para);
char	**split_grep(char **argv);
int		choose_redi(t_para *para, int i);
int		redi1(t_para *para, int i);
int		redi1_2(t_para *para, pid_t pid[2], int fd[2], int i);
void	rm_sp_grep(char **argv);
int		ft_exec_red(t_para *para, char *str);
int		ft_exec_red2(t_para *para, char **argv, char **all_path);
void	ft_freeee_split_redi(t_para *para);
int		redi2(t_para *para, int i);
int		redi2_1(t_para *para, int i, int fd[20], int j);
int		redi3(t_para *para, int i);
int		redi3_1(t_para *para, int i, int fd[20], int j);
void	file_eraser(t_para *para);
int		pipe_af_red(t_para *para, int i);
void	free_malloc(char *str);
void	free_malloc2(char **sp);
void	free_malloc_cd(char *str, t_para *para);
int		redi5(t_para *para, int i);
int		redi5_1(t_para *para, int i, int fd[20], int j);

#endif
