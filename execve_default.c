/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:21:38 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/17 18:54:31 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	free_exec(char **argv, char *path)
{
	free(argv);
	free(path);
}

int	ft_execve(t_para *para)
{
	char	*path;
	char	**argv;

	argv = malloc(sizeof(argv));
	if (!argv)
		error_handler(0, para);
	argv = ft_split(para->out, ' ');
	path = ft_strjoin("/bin/", argv[0]);
	if (fork() == 0)
	{
		if (execve(path, argv, para->env) == -1)
		{
			free_exec(argv, path);
			return (0);
		}
		else
		{
			free_exec(argv, path);
			return (1);
		}
	}
	else
		wait(NULL);
	free_exec(argv, path);
	return (1);
}
