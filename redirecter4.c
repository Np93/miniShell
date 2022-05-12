/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecter4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 22:11:34 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/12 05:06:17 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	redi4(t_para *para, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		file_eraser(para);
		return (redi4_1(para, i));
	}
	else
	{
		waitpid(pid, NULL, 0);
		unlink("tmp");
		return (0);
	}
	return (0);
}

int	redi4_1(t_para *para, int i)
{
	t_hd	*hd;

	hd = malloc(sizeof(hd) * 543);
	init_hd(hd);
	i = set_limit_and_red(hd, para, i);
	readline_hd(hd);
	if (is_redi_hd(hd, para) == 0)
		return (0);
	return (redi4_2(para, i, hd));
}

/*	if (i == 1)
	{
		pipe(hd->fdp);
		hd->pid = fork();
		if (hd->pid == 0)
		{
			(close(hd->fdp[1]), dup2(hd->fdp[0], STDIN), close(hd->fdp[0]));
			if (ft_exec_red(para, para->split_redi[i - 1]))
				return (i - 1);
		}
		else
		{
			hd->pid = fork();
			if (hd->pid == 0)
			{
				(close(hd->fdp[0]), dup2(hd->fdp[1], STDOUT));
				(close(hd->fdp[1]), execve("/bin/cat", hd->argv, para->env));
				return (0);
			}
			else
			{
				(close(hd->fdp[1]), close(hd->fdp[0]));
				waitpid(0, NULL, 0);
				exit(0);
				return (0);
			}
		}
	}
	else
		pipe_af_hd(para, i, hd);
	return (0);
}*/
int	redi4_2(t_para *para, int i, t_hd *hd)
{
	if (i == 1)
	{
		pipe(hd->fdp);
		hd->pid = fork();
		if (hd->pid == 0)
		{
			(close(hd->fdp[1]), dup2(hd->fdp[0], STDIN), close(hd->fdp[0]));
			if (ft_exec_red(para, para->split_redi[i - 1]))
				return (i - 1);
		}
		else
			return (redi4_3(para, hd));
	}
	else
		pipe_af_hd(para, i, hd);
	return (0);
}

int	redi4_3(t_para *para, t_hd *hd)
{
	hd->pid = fork();
	if (hd->pid == 0)
	{
		(close(hd->fdp[0]), dup2(hd->fdp[1], STDOUT));
		(close(hd->fdp[1]), execve("/bin/cat", hd->argv, para->env));
		return (0);
	}
	else
	{
		(close(hd->fdp[1]), close(hd->fdp[0]));
		waitpid(0, NULL, 0);
		exit(0);
		return (0);
	}
}
