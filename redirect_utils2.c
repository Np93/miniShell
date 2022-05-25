/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 00:33:52 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/25 16:42:54 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	file_opener(t_para *para)
{
	int	i;

	file_eraser(para);
	i = 0;
	while (para->split_redi[i] != NULL)
		i++;
	i -= 2;
	while (ft_strstr(para->split_redi[i], ">") && 1 <= i)
	{
		open(para->split_redi[i + 1],
			O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
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
}

int	ft_check_cmd(t_para *para)
{
	int	i;
	int	err;

	err = 0;
	i = 0;
	while (para->split_redi[i] != NULL)
	{
		if (para->split_redi[i] == NULL)
			break ;
		i = ft_check_cmd4(i, para);
		if (i == 0 || ft_strncmp(para->split_redi[i - 1], "|", 1) == 0)
			err += ft_check_cmd2(para, para->split_redi[i]);
		else if (para->split_redi[i - 1][0] == '<'
					&& para->split_redi[i - 1][1] == '\0')
		{
			if (access(para->split_redi[i], F_OK != 0))
			{
				printf("minishell: %s: No such file or directory 🐚\n",
					para->split_redi[i]);
				err++;
			}
		}
		i++;
	}
	return (err);
}

int	ft_check_cmd2(t_para *para, char *str)
{
	char	**all_path;
	char	**argv;

	if (ft_strstr(str, ">") || ft_strstr(str, "<"))
		return (0);
	if (ft_strstr(str, "grep") == 4)
	{
		argv = ft_split(str, 34);
		rm_sp_grep(argv);
	}
	else
		argv = ft_split(str, ' ');
	ft_check_path(argv);
	all_path = all_path_exec2(para, argv[0]);
	return (ft_check_cmd3(argv, all_path));
}

int	ft_check_cmd3(char **argv, char **all_path)
{
	int	i;

	i = 0;
	while (all_path[i] != NULL)
	{
		if (access(all_path[i], F_OK) == 0)
		{
			(free_malloc2(argv), free_malloc2(all_path));
			return (0);
		}
		else
			i++;
	}
	printf("minishell: %s: command not found 🐚\n", argv[0]);
	(free_malloc2(argv), free_malloc2(all_path));
	return (1);
}

int	ft_check_cmd4(int i, t_para *para)
{
	if (i == 0)
		return (0);
	if (ft_strstr(para->split_redi[i], "|"))
		i++;
	else if (ft_strstr(para->split_redi[i], ">"))
		i++;
	else if (ft_strstr(para->split_redi[i], "<")
		&& para->split_redi[i][1] == '\0')
		i++;
	return (i);
}
