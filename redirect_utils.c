/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:36:36 by rmonney           #+#    #+#             */
/*   Updated: 2022/04/25 20:09:57 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_freeee_split_redi(t_para *para)
{
	int		i;

	i = 0;
	while (para->split_redi[i] != NULL)
	{
		para->split_redi[i] = NULL;
		i++;
	}
}

int	choose_redi(t_para *para, int i)
{
	int	ret;

	ret = 0;
	if (ft_strstr(para->split_redi[i], "|"))
		ret = redi1(para, i);
/*	else if (ft_strstr(para->split_redi[i], ">>"))
		ret = redi2(para, i);
	else if (ft_strstr(para->split_redi[i], ">"))
		ret = redi3(para, i);
	else if (ft_strstr(para->split_redi[i], "<<"))
		ret = redi4(para, i);
	else if (ft_strstr(para->split_redi[i], "<"))
		ret = redi5(para, i);
*/
	return (ret);
}

int	ft_exec_red(t_para *para, char *str)
{
	char	**all_path;
	char	**argv;

	argv = malloc(sizeof(argv));
	if (!argv)
		error_handler(0, para);
	if (ft_strstr(str, "grep") == 4)
		argv = ft_split(str, 34);
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
