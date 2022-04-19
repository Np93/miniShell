/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:46:42 by rmonney           #+#    #+#             */
/*   Updated: 2022/04/19 23:58:46 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

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
	init_redi(para);

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
	if (exec_redi(para, i) == 0)
		printf("redirection kk\n");
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
	//   copie conforme //

	pipe(fd);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN);
		close(fd[0]);
		if (ft_exec_red(para, para->split_redi[i + 1]) == 1)
			return (1);
		else
		{
			printf("kk1\n");
			return (0);
		}
	}
	else
	{
		pid[1] = fork();
		if (pid[1] == 0)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT);
			close(fd[1]);
			if (1 < i)
			{
				if (exec_redi(para, (i - 2)) == 1)
					return (1);
				else
				{
					printf("kk2\n");
					return (0);
				}
			}
			else
			{
				if (ft_exec_red(para, para->split_redi[i - 1]) == 1)
					return (1);
				else
				{
					printf("kk3\n");
					return (0);
				}
			}
		}
		else
		{
			close(fd[0]);
			close(fd[1]);
			waitpid(pid[0], &status[0], 0);
			waitpid(pid[1], &status[1], 0);
			return (1);
		}
	}
	printf("kk4\n");
	return (0);
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

	i = 0;
	while (para->split_redi[i] != NULL)
	{
		printf("split %d = %s\n", i, para->split_redi[i]);
		i++;
	}
	printf("\n");

	i = 0;
	while (argv[i] != NULL)
	{
		printf("argv %d = %s\n", i, argv[i]);
		i++;
	}*/

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

char	**ft_freeee_split_redi(t_para *para)
{
	char	**ret;
	int		i;

	i = 0;
//	while (para->split_redi[i] != NULL)
//		i++;
//	i--;
//	while (i <= 0)
//		free(para->split_redi[i--]);
	if (para->split_redi)
		free(para->split_redi);
	ret = malloc(sizeof(char *) * 99);
	if (!ret)
		error_handler(0, para);
	return (ret);
}
