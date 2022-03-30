/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 23:11:51 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/30 23:50:22 by rmonney          ###   ########.fr       */
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
	int	a;

	a = -1;
	i = 0;
	while (para->current[i] != '\0')
	{
		i = search_redirect3(para, i);
		if (search_redirect2(para->current, i) != -1)
		{
			para->split_redi[++a] = cpy_bf_redi(para->current, i);
			para->split_redi[++a]
				= int_to_str_redi(search_redirect2(para->current, i));
			i += (search_redirect2(para->current, i) % 2) + 1;
		}
		else
			i++;
	}
	if (a != -1)
	{
		para->split_redi[++a] = cpy_bf_redi(para->current, i);
		return (1);
	}
	return (a + 1);
}
