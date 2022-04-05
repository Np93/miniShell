/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:46:42 by rmonney           #+#    #+#             */
/*   Updated: 2022/04/05 22:17:44 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	launch_redirect(t_para *para)
{
	int	a;

	a = -1;
	while (para->split_redi[++a] != NULL)
	{
		if (!(a % 2))
			para->split_redi[a] = unquoter(para->split_redi[a], para);
	}
	a = -1;
	while (para->split_redi[++a] != NULL)
		printf("split no %d = %s\n", a, para->split_redi[a]);
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
	p->str = malloc(sizeof(char) * ft_strlen(str) * 99);
	if (!p->str)
		error_handler(0, para);
	ret = malloc(sizeof(char *));
	if (!ret)
		error_handler(0, para);
	unquoter6(para, p, str);
	ret = ft_strdup(p->str);
	free(p);
	free(str);
	return (ret);
}

int	unquoter6(t_para *para, t_parse *p, char *str)
{
	while (str[p->i] != '\0')
	{
		if (str[p->i] == 39 || str[p->i] == 34)
		{
			if (!unquoter4(para, p, str))
				return (1);
		}
		else if (str[p->i] == '$')
			unquoter2(para, p, str);
		else
			if (unquoter5(p, str))
				return (unquoter5(p, str));
	}
	p->str[p->j] = '\0';
	return (0);
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

	int		a = -1;
	while (argv[++a] != NULL)
		printf ("argv nº%d = %s\n", a, argv[a]);

//	argv = split_redirect(argv);
	return (0);
}
