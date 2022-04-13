/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_redirect3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:31:42 by rmonney           #+#    #+#             */
/*   Updated: 2022/04/13 18:24:27 by rmonney          ###   ########.fr       */
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
			return (0);
		return (1);
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
	char **argv;

	argv = ft_split(para->out, '\"');
//	if (ft_strstr(argv[2], " "))
//		argv = split_grep(argv);
	int a = -1;
	while (argv[++a] != NULL)
		printf("arg %d = '%s'\n", a, argv[a]);
	if (execve("/usr/bin/grep", argv, para->env) == -1)
	{
		free(argv);
		return (0);
	}
	else
	{
		free(argv);
		return (1);
	}
}

char	**split_grep(char **argv)
{
	(void)argv;
	// virer les espace de mert et ev ceux de larg 2
	return (NULL);
}
