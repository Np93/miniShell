/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_redirect2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 22:11:56 by rmonney           #+#    #+#             */
/*   Updated: 2022/04/21 17:31:54 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	grep_spec2(t_parse *p, char *str)
{
	p->i++;
	while (str[p->i] != 39)
		p->str[p->j++] = str[p->i++];
	p->i++;
}

void	grep_spec3(t_para *para, t_parse *p, char *str)
{
	p->i++;
	while (str[p->i] != 34)
	{
		if (str[p->i] == 92)
		{
			if (str[p->i + 1] == 92)
			{
				p->str[p->j++] = 92;
				p->i += 2;
			}
			else
				p->i++;
		}
		else if (str[p->i] == '$')
			unquoter2(para, p, str);
		else
			p->str[p->j++] = str[p->i++];
	}
	p->i++;
}

void	grep_spec4(t_para *para, t_parse *p, char *str)
{
	if (str[p->i] == 92)
	{
		if (str[p->i + 1] == 92)
		{
			p->str[p->j++] = 92;
			p->i += 2;
		}
		else
			p->i++;
	}
	else if (str[p->i] == '$')
		unquoter2(para, p, str);
	else
		p->str[p->j++] = str[p->i++];
}

void	grep_spec5(t_para *para, t_parse *p, char *str)
{
	if (str[0] == 34 || str[0] == 39)
		p->i = 6;
	else
		p->i = 4;
	while (str[p->i] == ' ')
		p->i++;
	grep_spec1(p);
	if (str[p->i] == 39)
		grep_spec2(p, str);
	else if (str[p->i] == 34)
		grep_spec3(para, p, str);
	else
	{
		while (str[p->i] != ' ' && str[p->i] != '\0')
		{
			if (str[p->i] == 39)
				grep_spec2(p, str);
			else if (str[p->i] == 34)
				grep_spec3(para, p, str);
			else
				grep_spec4(para, p, str);
		}
	}
}
