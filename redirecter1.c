/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecter1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:47:16 by rmonney           #+#    #+#             */
/*   Updated: 2022/04/25 20:23:21 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	redi1(t_para *para, int i)
{
	int		fd[2];
	pid_t	pid[2];

	pipe(fd);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		(close(fd[1]), dup2(fd[0], STDIN), close(fd[0]));
		if (ft_exec_red(para, para->split_redi[i + 1]))
			return (i + 1);
	}
	else
	{
		return (redi1_2(para, pid, fd, i));
	}
	return (0);
}

int	redi1_2(t_para *para, pid_t pid[2], int fd[2], int i)
{
	pid[1] = fork();
	if (pid[1] == 0)
	{
		(close(fd[0]), dup2(fd[1], STDOUT), close(fd[1]));
		if (1 < i)
		{
			if (choose_redi(para, (i - 2)))
				return (1 - 2);
		}
		else
		{
			if (ft_exec_red(para, para->split_redi[i - 1]))
				return (i - 1);
		}
	}
	else
	{
		(close(fd[1]), close(fd[0]));
		(waitpid(pid[1], NULL, 0), waitpid(pid[0], NULL, 0));
		return (0);
	}
	return (0);
}
