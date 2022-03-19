/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:21:38 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/19 18:54:03 by rmonney          ###   ########.fr       */
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
	all_path[i] = NULL;
	i = -1;
	while (all_path[++i] != NULL)
	{
		all_path[i] = ft_strjoin(all_path[i], "/");
		all_path[i] = ft_strjoin(all_path[i], end);
	}
	return (all_path);
}

int	exec_and_return(char **all_path, char **argv, t_para *para)
{
	int	i;

	i = -1;
	while (all_path[++i] != NULL)
	{
		if (access(all_path[i], X_OK) == 0)
		{
			if (fork() == 0)
			{
				if (execve(all_path[i], argv, para->env) == -1)
					continue ;
			}
			else
			{
				wait(NULL);
				free_exec(argv, all_path);
				return (1);
			}
		}
	}
	free_exec(argv, all_path);
	return (0);
}

int	ft_execve(t_para *para)
{
	char	**all_path;
	char	**argv;

	argv = malloc(sizeof(argv));
	if (!argv)
		error_handler(0, para);
	all_path = NULL;
	argv = ft_split(para->out, ' ');
	ft_check_path(argv);
	all_path = all_path_exec(para, argv[0]);
	return (exec_and_return(all_path, argv, para));
}
