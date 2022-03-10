/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   current_parser2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 18:52:40 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/10 22:41:44 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*  92 = \  //  39 = '  //  34 = "  */

int	current_parser5(t_para *para, t_parse *p)
{
	if (para->current[p->i] == ';')
		return (2);
	else if (para->current[p->i] == 92)
	{
		if (para->current[p->i + 1] == 92)
		{
			p->str[p->j++] = 92;
			p->i += 2;
		}
		else
			p->i++;
	}
	else
		p->str[p->j++] = para->current[p->i++];
	return (0);
}

int	current_parser6(t_para *para, t_parse *p)
{
	while (para->current[p->i] != '\0')
	{
		if (para->current[p->i] == 39 || para->current[p->i] == 34)
		{
			if (!current_parser4(para, p))
				return (1);
		}
		else if (para->current[p->i] == '$')
			current_parser2(para, p);
		else
			if (current_parser5(para, p))
				return (current_parser5(para, p));
	}
	p->str[p->j] = '\0';
	return (0);
}
