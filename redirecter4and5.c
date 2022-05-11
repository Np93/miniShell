/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecter4and5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhirzel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 19:53:20 by nhirzel           #+#    #+#             */
/*   Updated: 2022/05/11 23:32:57 by nhirzel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	redi4(t_para *para, int i)
{
	int		fd[20];
	int		j;
	pid_t	pid;

	pid = fork();
	j = 0;
	if (pid == 0)
	{
		return (redi4_1(para, i, fd, j));
	}
	else
	{
		waitpid(pid, NULL, 0);
		unlink(para->split_redi[i + 1]);
		return (0);
	}
	return (0);
}

int	redi4_1(t_para *para, int i, int fd[20], int j)
{
	char	*line;

	line = ft_strdup("");
	fd[j] = open(para->split_redi[i + 1],
			O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	while (ft_strcmp(line, para->split_redi[i + 1]) != 0)
	{
		free(line);
		line = readline("> ");
		if (ft_strcmp(line, para->split_redi[i + 1]) != 0)
			ft_putendl_fd(line, fd[j]);
	}
//	close(fd[j]);
//	free(line);
	return(redi5_1(para, i, fd, j));
//	return (pipe_af_red(para, i));
}

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
				printf("Error: No such file or directory ╭∩╮(･◡･)╭∩╮\n");
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
