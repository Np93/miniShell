/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:46:42 by rmonney           #+#    #+#             */
/*   Updated: 2022/04/12 23:08:39 by rmonney          ###   ########.fr       */
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
		{
			if ((ft_strstr(para->split_redi[a], "grep") == 4
					|| ft_strstr(para->split_redi[a], "grep") == 5)
				&& (para->split_redi[a][0] == 'g'
				|| para->split_redi[a][0] == 34
				|| para->split_redi[a][0] == 39))
				para->split_redi[a] = grep_spec(para->split_redi[a], para, 0);
			else
				para->split_redi[a] = unquoter(para->split_redi[a], para);
		}
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
