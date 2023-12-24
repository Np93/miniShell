/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_redirect3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:31:42 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/03 19:54:11 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	grepr(t_para *para)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (grepxec(para) == 0)
			exit(0);
		exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_glob.exit_status = WEXITSTATUS(status);
		return (1);
	}
}

int	grepxec(t_para *para)
{
	char	**argv;

	argv = ft_split(para->out, '\"');
	if (argv[2] != NULL)
		argv = split_grep(argv);
	if (execve("/usr/bin/grep", argv, para->env) == -1)
	{
		free_malloc2(argv);
		return (0);
	}
	else
	{
		free_malloc2(argv);
		return (1);
	}
}

char	**split_grep(char **argv)
{
	int		i;
	char	**split;

	i = 0;
	split = ft_split(argv[2], ' ');
	while (split[i + 1] != NULL)
		i++;
	if (i == 0)
	{
		free(argv[2]);
		argv[2] = ft_strdup(split[0]);
	}
	else
	{
		i = -1;
		while (split[++i] != NULL)
			argv[i + 2] = ft_strdup(split[i]);
		argv[i + 2] = NULL;
	}
	free_malloc2(split);
	return (argv);
}
