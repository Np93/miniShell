/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 00:33:52 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/24 01:11:17 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_check_cmd(t_para *para)
{
	int	i;
	int	err;

	err= 0;
	i = 0;
	while (para->split_redi[i] != NULL)
	{
		i += ft_check_cmd4(para->split_redi[i]);
		if (i == 0 || ft_strncmp(para->split_redi[i - 1], "|", 1) == 0)
			err += ft_check_cmd2(para, para->split_redi[i]);
		else if (i != 0 && para->split_redi[i - 1][0] == '<'
					&& para->split_redi[i - 1][1] == '\0')
		{
			if (access(para->split_redi[i], F_OK != 0))
			{
				printf("minishell: %s: No such file or directory\n",
					para->split_redi[i]);
				return (1);
			}
		}
		i++;
	}
	if (err != 0)
		return (1);
	return (0);
}

int	ft_check_cmd2(t_para *para, char *str)
{
	char	**all_path;
	char	**argv;

	argv = malloc(sizeof(argv));
	if (!argv)
		error_handler(0, para);
	if (ft_strstr(str, "grep") == 4)
	{
		argv = ft_split(str, 34);
		rm_sp_grep(argv);
	}
	else
		argv = ft_split(str, ' ');
	ft_check_path(argv);
	all_path = all_path_exec(para, argv[0]);
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
			(free(argv), free(all_path));
			return (0);
		}
		else
			i++;
	}
	printf("minishell: %s: command not found\n", argv[0]);
	(free(argv), free(all_path));
	return (1);
}

int	ft_check_cmd4(char *str)
{
	if (ft_strstr(str, "|"))
		return (1);
	if (ft_strstr(str, ">"))
		return (1);
	if (ft_strstr(str, "<"))
		return (1);
	return (0);
}
