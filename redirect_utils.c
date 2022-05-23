/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:36:36 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/23 23:37:58 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_freeee_split_redi(t_para *para)
{
	int	i;

	i = -1;
	if (para->redi == 1)
	{
		while (para->split_redi[++i] != NULL)
			free(para->split_redi[i]);
		free(para->split_redi);
		para->redi = 0;
	}
	else
		free(para->split_redi);
	para->redi = 0;
}

int	choose_redi(t_para *para, int i)
{
	int	ret;

	ret = 0;
	if (ft_strstr(para->split_redi[i], "|"))
		ret = redi1(para, i);
	else if (ft_strstr(para->split_redi[i], ">>"))
		ret = redi2(para, i);
	else if (ft_strstr(para->split_redi[i], ">"))
		ret = redi3(para, i);
	else if (ft_strstr(para->split_redi[i], "<<"))
		ret = redi4(para, i);
	else if (ft_strstr(para->split_redi[i], "<"))
		ret = redi5(para, i);
	return (ret);
}

void	rm_sp_grep(char **argv)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (argv[++i] != NULL)
	{
		j = 0;
		if (argv[i][0] == ' ')
		{
			tmp = malloc(sizeof(ft_strlen(argv[i])) + 1);
			while (argv[i][++j] != '\0')
				tmp[j - 1] = argv[i][j];
			tmp[j - 1] = '\0';
			free(argv[i]);
			argv[i] = tmp;
			free(tmp);
		}
	}
}

int	ft_exec_red(t_para *para, char *str)
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
	return (ft_exec_red2(para, argv, all_path));
}

int	ft_exec_red2(t_para *para, char **argv, char **all_path)
{
	int	i;

	i = 0;
	while (all_path[i] != NULL)
	{
		if (access(all_path[i], F_OK) == 0)
		{
			if (execve(all_path[i], argv, para->env) == -1)
			{
				(free(argv), free(all_path));
				return (1);
			}
			else
			{
				(free(argv), free(all_path));
				return (0);
			}
		}
		else
			i++;
	}
	(free(argv), free(all_path));
	return (1);
}
