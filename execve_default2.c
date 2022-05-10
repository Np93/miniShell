/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_default2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:50:46 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/10 02:44:40 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*last_path(char *arg)
{
	char	**path;
	char	*ret;
	int		i;

	i = 0;
	path = ft_split(arg, '/');
	while (path[i + 1] != NULL)
		i++;
	ret = ft_strdup(path[i]);
	free(arg);
	free(path);
	return (ret);
}

void	ft_check_path(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		if (ft_strstr(argv[i], "/bin/"))
		{
			argv[i] = last_path(argv[i]);
			i++;
		}
		else
			i++;
	}
}

int	check_bin(char **argv)
{
	int	i;

	i = -1;
	while (argv[++i] != NULL)
	{
		if (ft_strstr(argv[i], "/bin/"))
			return (1);
	}
	return (0);
}

int	exec_bin(char **argv, t_para *para)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(argv[0], argv, para->env) == -1)
			exit(0);
		exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_glob.exit_status = WEXITSTATUS(status);
		free_malloc2(argv);
		return (1);
	}
	return (0);
}
