/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 04:10:51 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/12 04:54:20 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	is_redi_hd(t_hd *hd, t_para *para)
{
	if (hd->fdin < 0)
	{
		kill(0, SIGUSR1);
		if (para->bait)
			free(para->bait);
		para->bait = ft_strdup(para->split_redi[-(hd->fdin)]);
		error_handler(9, para);
		return (0);
	}
	if (hd->fdout != 0 && 0 <= hd->fdin)
		dup2(hd->fdout, STDOUT);
	if (hd->fdin != 0)
		hd->argv[1] = ft_strdup(para->split_redi[hd->fdin]);
	else
		hd->argv[1] = ft_strdup("tmp");
	return (1);
}

int	pipe_af_hd(t_para *para, int i, t_hd *hd)
{
	int		fd[2];

	pipe(fd);
	hd->pid = fork();
	if (hd->pid == 0)
	{
		(close(fd[1]), dup2(fd[0], STDIN), close(fd[0]));
		if (ft_exec_red(para, para->split_redi[i - 1]))
			return (i - 1);
	}
	else
		return (pipe_af_hd1(para, fd, i, hd));
	return (0);
}

int	pipe_af_hd1(t_para *para, int fd[2], int i, t_hd *hd)
{
	hd->pid = fork();
	if (hd->pid == 0)
	{
		(close(fd[0]), dup2(fd[1], STDOUT), close(fd[1]));
		if (1 < i)
		{
			if (pipe_af_hd(para, (i - 2), hd))
				return (i - 2);
		}
		else
		{
			execve("/bin/cat", hd->argv, para->env);
			return (0);
		}
	}
	else
	{
		(close(fd[1]), close(fd[0]));
		waitpid(0, NULL, 0);
		return (0);
	}
	return (0);
}
