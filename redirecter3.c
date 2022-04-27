/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecter3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:26:32 by rmonney           #+#    #+#             */
/*   Updated: 2022/04/27 20:31:47 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	redi3(t_para *para, int i)
{
	int		fd[20];
	int		j;
	pid_t	pid;

	pid = fork();
	j = 0;
	if (pid == 0)
		return (redi3_1(para, i, fd, j));
	else
	{
		waitpid(pid, NULL, 0);
		return (0);
	}
	return (0);
}

int	redi3_1(t_para *para, int i, int fd[20], int j)
{
	while (ft_strstr(para->split_redi[i], ">"))
	{
		fd[j++] = open(para->split_redi[i + 1],
				O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
		if (1 < i)
		{
			if (ft_strstr(para->split_redi[i - 2], ">"))
				i -= 2;
			else
				break ;
		}
		else
			break ;
	}
	dup2(fd[0], STDOUT);
	if (1 < i)
	{
		if (choose_redi(para, (i - 2)))
			return (i - 2);
	}
	else
		if (ft_exec_red(para, para->split_redi[i - 1]))
			return (i - 1);
	return (0);
}
