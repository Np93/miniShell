/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:46:42 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/30 23:52:50 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	launch_redirect(t_para *para)
{
	int	a;

	a = 0;
	while (para->split_redi[a] != NULL)
	{
		printf("arg no %d = '%s'\n", a, para->split_redi[a]);
		a++;
	}
}

int	exec_redirect1(t_para *para)
{
	char	**all_path;
	char	**argv;

	argv = malloc(sizeof(argv));
	if (!argv)
		error_handler(0, para);
	argv = ft_split(para->out, ' ');
	ft_check_path(argv);
	all_path = all_path_exec(para, argv[0]);
//	argv = split_redirect(argv);
	return (0);
}
