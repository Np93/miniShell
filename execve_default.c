/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:21:38 by rmonney           #+#    #+#             */
/*   Updated: 2022/04/05 20:56:05 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	free_exec(char **argv, char **path)
{
	free(argv);
	free(path);
}

char	**all_path_exec(t_para *para, char *end)
{
	char	**all_path;
	char	*path;
	int		i;

	i = 0;
	all_path = malloc(sizeof(all_path));
	if (!all_path)
		error_handler(0, para);
	path = ft_getenv(para, "PWD");
	all_path = ft_split(ft_getenv(para, "PATH"), ':');
	while (all_path[i] != NULL)
		i++;
	all_path[i++] = path;
	if (ft_strstr(end, "/"))
		all_path[i++] = end;
	all_path[i] = NULL;
	i = -1;
	while (all_path[++i] != NULL)
	{
		all_path[i] = ft_strjoin(all_path[i], "/");
		all_path[i] = ft_strjoin(all_path[i], end);
	}
	return (all_path);
}

int	exec_and_return2(char **all_path, char **argv, t_para *para, int i)
{
	pid_t	pid;
	int		status;

	if (access(all_path[i], F_OK) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(all_path[i], argv, para->env) == -1)
				return (0);
			return (1);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				g_glob.exit_status = WEXITSTATUS(status);
			free_exec(argv, all_path);
			return (1);
		}
	}
	else
		return (0);
}

int	exec_and_return(char **all_path, char **argv, t_para *para)
{
	int		i;
	int		ret;

	i = -1;
	while (all_path[++i] != NULL)
	{
		ret = exec_and_return2(all_path, argv, para, i);
		if (ret == 0)
			continue ;
		else
			return (1);
	}
	free_exec(argv, all_path);
	return (0);
}

int	ft_execve(t_para *para)
{
	char	**all_path;
	char	**argv;

	all_path = NULL;
	argv = malloc(sizeof(argv));
	if (!argv)
		error_handler(0, para);
	argv = ft_split(para->out, ' ');
	ft_check_path(argv);
	all_path = all_path_exec(para, argv[0]);
	return (exec_and_return(all_path, argv, para));
}
