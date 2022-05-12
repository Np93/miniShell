/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecter5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhirzel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 19:53:20 by nhirzel           #+#    #+#             */
/*   Updated: 2022/05/12 05:05:48 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	redi5(t_para *para, int i)
{
	int		fd[20];
	int		j;
	pid_t	pid;

	pid = fork();
	j = 0;
	if (pid == 0)
	{
		return (redi5_1(para, i, fd, j));
	}
	else
	{
		waitpid(pid, NULL, 0);
		return (0);
	}
	return (0);
}

int	redi5_1(t_para *para, int i, int fd[20], int j)
{
	while (ft_strstr(para->split_redi[i], "<"))
	{
		fd[j++] = open(para->split_redi[i + 1],
				O_RDONLY, S_IRUSR | S_IWUSR);
		if (fd[j - 1] == -1)
		{
			if (ft_strcmp("<<", para->split_redi[i]) != 0)
			{
				printf("zsh: no such file or directory\n");
				return (0);
			}
		}
		if (1 < i)
		{
			if (ft_strstr(para->split_redi[i - 2], "<"))
				i -= 2;
			else
				break ;
		}
		else
			break ;
	}
	dup2(fd[0], STDIN);
	return (pipe_af_red(para, i));
}
