/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 23:11:51 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/13 08:52:58 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*    34 = "    39 = '    */

int	search_redirect2(char *str, int i)
{
	if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (1);
		else
			return (0);
	}
	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return (3);
		else
			return (2);
	}
	if (str[i] == '|')
		return (4);
	return (-1);
}

int	search_redirect3(t_para *para, int i)
{
	if (para->current[i] == 34)
	{
		i++;
		while (para->current[i] != 34)
			i++;
	}
	if (para->current[i] == 39)
	{
		i++;
		while (para->current[i] != 39)
			i++;
	}
	return (i);
}

int	search_redirect(t_para *para)
{
	int	i;

	para->a = -1;
	i = 0;
	if (para->current[0] == '<')
		i = search_redirect4(para, i);
	else
		i = search_redirect5(para, i);
	if (para->a != -1 && para->current[0] != '<')
	{
		para->split_redi[++para->a] = cpy_bf_redi(para->current, i);
		return (1);
	}
	if (para->a != -1)
		para->redi = 1;
	return (para->a + 1);
}

char	*grep_spec(char *str, t_para *para, int mod)
{
	char	*ret;
	t_parse	*p;

	if ((ft_strstr(str, "grep") == 4 || ft_strstr(str, "grep") == 5)
		&& (str[0] == 34 || str[0] == 39 || str[0] == 'g'))
	{
		p = malloc(sizeof(t_parse));
		if (p)
			p->str = malloc(sizeof(char) * ft_strlen(str) * 99);
		if (!p->str || !p)
			error_handler(0, para);
	}
	else
		return (str);
	grep_spec5(para, p, str);
	p->str[p->j++] = 34;
	unquoter6(para, p, str);
	ret = ft_strdup(p->str);
	if (mod == 0)
		free(str);
	(free(p->str), free(p));
	return (ret);
}

void	grep_spec1(t_parse *p)
{
	p->str[0] = 'g';
	p->str[1] = 'r';
	p->str[2] = 'e';
	p->str[3] = 'p';
	p->str[4] = 34;
	p->j = 5;
}
