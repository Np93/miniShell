/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquoter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:58:19 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/31 18:10:04 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*  92 = \  //  39 = '  //  34 = "  */

void	current_parser2(t_para *para, t_parse *p, char *str)
{
	p->k = 0;
	p->tmp = get_dollar(str, ++p->i, para);
	if (str[p->i] == '?')
		p->i++;
	else
	{
		while (str[p->i] != ' ' && str[p->i] != 39
			&& str[p->i] != 34 && str[p->i] != '\0')
			p->i++;
	}
	while (p->tmp[p->k] != '\0')
		p->str[p->j++] = p->tmp[p->k++];
}

int	unquoter3(t_para *para, t_parse *p, char *str)
{
	p->i++;
	while (str[p->i] != 34 && str[p->i] != '\0')
	{
		if (str[p->i] == '$')
		{
			unquoter2(para, p, str);
			if (str[p->i] == '\0')
				return (0);
		}
		else if (str[p->i] == 92)
			unquoter7(para, p, str);
		else
			p->str[p->j++] = str[p->i++];
	}
	if (str[p->i] != 34)
		return (0);
	p->i++;
	return (1);
}

int	unquoter4(t_para *para, t_parse *p, char *str)
{
	if (str[p->i] == 39)
	{
		p->i++;
		while (str[p->i] != 39 && str[p->i] != '\0')
			p->str[p->j++] = str[p->i++];
		if (str[p->i] != 39)
			return (0);
		p->i++;
	}
	else if (str[p->i] == 34)
	{
		if (!unquoter3(para, p, str))
			return (0);
	}
	return (1);
}

int	unquoter5(t_para *para, t_parse *p, char *str)
{
	if (str[p->i] == ';')
		return (2);
	else if (str[p->i] == 92)
	{
		if (str[p->i + 1] == 92)
		{
			p->str[p->j++] = 92;
			p->i += 2;
		}
		else
			p->i++;
	}
	else
		p->str[p->j++] = str[p->i++];
	return (0);
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
			if (unquoter5(para, p))
				return (unquoter5(para, p, str));
	}
	p->str[p->j] = '\0';
	return (0);
}

void	unquoter7(t_para *para, t_parse *p, char *str)
{
	if (str[p->i + 1] == 92)
	{
		p->str[p->j++] = 92;
		p->i += 2;
	}
	else
		p->i++;
}
