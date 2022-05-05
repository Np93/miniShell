/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecter4and5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhirzel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 19:53:20 by nhirzel           #+#    #+#             */
/*   Updated: 2022/03/10 19:53:53 by nhirzel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, &"\n", 1);
}

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
	close(fd[j]);
	free(line);
	redi5_1(para, i, fd, j);
	return (pipe_af_red(para, i));
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
		fd[j] = open(para->split_redi[i + 1],
				O_RDONLY, S_IRUSR | S_IWUSR);
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
