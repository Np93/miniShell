/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:46:42 by rmonney           #+#    #+#             */
/*   Updated: 2022/04/21 17:37:37 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	cat_exec(char **env);	//1
int	wc_exec(char **env);	//3
int	grep_exec(char **env);	//2
int	piper(char **env);
int	piper2(char **env);

void	launch_redirect(t_para *para)
{
	int	a;

	a = -1;
	while (para->split_redi[++a] != NULL)
	{
		if (!(a % 2))
		{
			if ((ft_strstr(para->split_redi[a], "grep") == 4
					|| ft_strstr(para->split_redi[a], "grep") == 5)
				&& (para->split_redi[a][0] == 'g'
				|| para->split_redi[a][0] == 34
				|| para->split_redi[a][0] == 39))
				para->split_redi[a] = grep_spec(para->split_redi[a], para, 0);
			else
				para->split_redi[a] = unquoter(para->split_redi[a], para);
		}
	}

	a = 0;
	while (para->split_redi[a] != NULL)
		a++;
	if (3 < a)
	{
		g_glob.main = 0;
		a = fork();
		if (a == 0)
		{
			init_redi(para);
			close(STDIN);
		}
		else
			waitpid(a, NULL, 0);
		g_glob.main = 1;
	}
	else
		init_redi(para);

//	piper(para->env);

/*	a = -1;
	while (para->split_redi[++a] != NULL)
		printf("split no %d = %s\n", a, para->split_redi[a]);*/
}

char	*unquoter(char *str, t_para *para)
{
	char	*ret;
	t_parse	*p;

	p = malloc(sizeof(t_parse));
	if (!p)
		error_handler(0, para);
	p->i = 0;
	p->j = 0;
	p->str = malloc(sizeof(char) * ft_strlen(str) * 99);
	if (!p->str)
		error_handler(0, para);
	ret = malloc(sizeof(char *));
	if (!ret)
		error_handler(0, para);
	unquoter6(para, p, str);
	ret = ft_strdup(p->str);
	free(p);
	free(str);
	return (ret);
}

int	unquoter6(t_para *para, t_parse *p, char *str)
{
	while (str[p->i] != '\0')
	{
		if (str[p->i] == 39 || str[p->i] == 34)
		{
			if (!unquoter4(para, p, str))
				return (1);
		}
		else if (str[p->i] == '$')
			unquoter2(para, p, str);
		else
			if (unquoter5(p, str))
				return (unquoter5(p, str));
	}
	p->str[p->j] = '\0';
	return (0);
}

void	init_redi(t_para *para)
{
	int	i;

	i = 0;
	while (para->split_redi[i] != NULL)
		i++;
	i -= 2;
	exec_redi(para, i);
//		printf("redirection kk\n");
	//	error_handler(10, para);
}

int	exec_redi(t_para *para, int i)
{
	int	ret;

	ret = 1;
	if (ft_strstr(para->split_redi[i], "|"))
		ret = redi1(para, i);
/*	else if (ft_strstr(para->split_redi[i], ">>"))
		ret = redi2(para, i);
	else if (ft_strstr(para->split_redi[i], ">"))
		ret = redi3(para, i);
	else if (ft_strstr(para->split_redi[i], "<<"))
		ret = redi4(para, i);
	else if (ft_strstr(para->split_redi[i], "<"))
		ret = redi5(para, i);
*/
	if (ret == 1)
		return (1);
	else
		return (0);
}

int	redi1(t_para *para, int i)
{
	int		fd[2];
	int		status[2];
	pid_t	pid[2];
	
	pipe(fd);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN);
		close(fd[0]);
		ft_exec_red(para, para->split_redi[i + 1]);
	}
	else if (pid[0] == -1)
		printf("fork1 failed\n");
	else
	{
		pid[1] = fork();
		if (pid[1] == 0)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT);
			close(fd[1]);
			if (1 < i)
				exec_redi(para, (i - 2));
			else
				ft_exec_red(para, para->split_redi[i - 1]);
		}
		else if (pid[1] == -1)
			printf("fork2 failed\n");
		else
		{
			close(fd[0]);
			close(fd[1]);
			waitpid(pid[1], &status[1], 0);
			waitpid(pid[0], &status[0], 0);
			return (1);
		}
	}
	return (1);
}

int	ft_exec_red(t_para *para, char *str)
{
	char	**all_path;
	char	**argv;
	int		i;

	argv = malloc(sizeof(argv));
	if (!argv)
		error_handler(0, para);
	if (ft_strstr(str, "grep") == 4)
		argv = ft_split(str, 34);
	else
		argv = ft_split(str, ' ');
	ft_check_path(argv);
	all_path = all_path_exec(para, argv[0]);
	
/*	i = -1;
	while (all_path[++i] != NULL)
		printf("path = %s\n", all_path[i]);
	printf("\n");
*/
/*	i = 0;
	while (para->split_redi[i] != NULL)
	{
		printf("split_redi %d = %s\n", i, para->split_redi[i]);
		i++;
	}
	printf("\n");
*/
/*	i = 0;
	while (argv[i] != NULL)
	{
		printf("argv %d = %s\n", i, argv[i]);
		i++;
	}
*/
	i = 0;
	while (all_path[i] != NULL)
	{
		if (access(all_path[i], F_OK) == 0)
		{
			if (execve(all_path[i], argv, para->env) == -1)
				i++;
			else
			{
				(free(argv), free(all_path));
				return (1);
			}
		}
		else
			i++;
	}
	(free(argv), free(all_path));
	return (0);
}

void	ft_freeee_split_redi(t_para *para)
{
	int		i;

	i = 0;
	while (para->split_redi[i] != NULL)
	{
		para->split_redi[i] = NULL;
		i++;
	}
}

int	cat_exec(char **env)
{
	char	**argv;

	argv = malloc(sizeof(char *) * 2);
	argv[0] = "cat";
	argv[1] = "livre.txt";
	argv[2] = NULL;
	if (execve("/bin/cat", argv, env) == -1)
	{
		printf("execve of cat failed\n");
		return (0);
	}
	else
		return (1);
}

int	wc_exec(char **env)
{
	char	**argv;

	argv = malloc(sizeof(char *) * 2);
	argv[0] = "wc";
	argv[1] = "-l";
	argv[3] = NULL;
	if (execve("/usr/bin/wc", argv, env) == -1)
	{
		printf("execve of wc failed\n");
		return (0);
	}
	else
		return (1);
}

int	grep_exec(char **env)
{
	char	**argv;

	argv = malloc(sizeof(char *) * 3);
	argv[0] = "grep";
	argv[1] = "his";
	argv[2] = NULL;
	if (execve("/usr/bin/grep", argv, env) == -1)
	{
		printf("execve of grep failed\n");
		return (0);
	}
	else
		return (1);
}

int	piper(char **env)
{
	int		fd[2];
	int		status1;
	int		status2;
	pid_t	pid1;
	pid_t	pid2;

	pipe(fd);
	pid1 = fork();
	if (pid1 == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		if (wc_exec(env) == 1)
			return (1);
		else
			return (0);
	}
	else
	{
		pid2 = fork();
		if (pid2 == 0)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			if (piper2(env) == 1)
				return (1);
			else
				return (0);
		}
		else
		{
			close(fd[0]);
			close(fd[1]);
			waitpid(pid2, &status2, 0);
			waitpid(pid1, &status1, 0);
			return (1);
		}
	}
	return (0);
}

int	piper2(char **env)
{
	int		fd[2];
	int		status1;
	int		status2;
	pid_t	pid1;
	pid_t	pid2;

	pipe(fd);
	pid1 = fork();
	if (pid1 == 0)
	{
		(close(fd[1]), dup2(fd[0], STDIN_FILENO), close(fd[0]));
		if (grep_exec(env) == 1)
			return (1);
		else
			return (0);
	}
	else
	{
		pid2 = fork();
		if (pid2 == 0)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			if (cat_exec(env) == 1)
				return (1);
			else
				return (0);
		}
		else
		{
			close(fd[0]);
			close(fd[1]);
			waitpid(pid2, &status2, 0);
			waitpid(pid1, &status1, 0);
			return (1);
		}
	}
	return (0);
}
