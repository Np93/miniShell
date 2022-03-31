/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:46:42 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/31 17:48:23 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	launch_redirect(t_para *para)
{
	int	a;

	a = 0;
	while (para->split_redi[a] != NULL)
	{
		printf("split no %d = %s\n", a, para->split_redi[a]);
//		split_redi[a] = unquoter(split_redi[a], para);
		a++;
	}
}

char	*unquoter(char *str, t_para *para)
{
	char	*ret;
	t_parse	*p;

	p = malloc(sizeof(t_parse));
	if (!p)
		error_handler(0, para);
	p->i = 0;
	p->j = 0;
	p->str = malloc(sizeof(char *));
	if (!p->str)
		error_handler(0, para);
	ret = malloc(sizeof(char *));
	if (!ret)
		error_handler(0, para);
//	unquoter6(str, p, para);
	ret = ft_strdup(p->str);
	free(p);
	free(str);
	return (ret);
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
