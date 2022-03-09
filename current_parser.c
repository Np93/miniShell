/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   current_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 18:55:51 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/09 23:46:31 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/* 39 = ' // 34 = " */

char	*get_dollar(char *current, int i, t_para *para)
{
	char	arg[999];
	int		j;
	char	*ret;

	j = 0;
	while (current[i] != ' ' && current[i] != 34
		&& current[i] != 39 && current[i] != '\0')
		arg[j++] = current[i++];
	arg[j] = '\0';
	ret = ft_getenv(para, arg);
	if (ret != NULL)
		return (ret);
	else
		return (strdup(""));
}

void	current_parser2(t_para *para, t_parse *p)
{
	p->k = 0;
	p->tmp = get_dollar(para->current, ++p->i, para);
	while (para->current[p->i] != ' ' && para->current[p->i] != 39
		&& para->current[p->i] != 34 && para->current[p->i] != '\0')
		p->i++;
	while (p->tmp[p->k] != '\0')
		p->str[p->j++] = p->tmp[p->k++];
}

int	current_parser3(t_para *para, t_parse *p)
{
	p->i++;
	while (para->current[p->i] != 34 && para->current[p->i] != '\0')
	{
		if (para->current[p->i] == '$')
		{
			current_parser2(para, p);
			if (para->current[p->i] == '\0')
				return (0);
		}
		else
			p->str[p->j++] = para->current[p->i++];
	}
	if (para->current[p->i] != 34)
		return (0);
	p->i++;
	return (1);
}

int	current_parser4(t_para *para, t_parse *p)
{
	if (para->current[p->i] == 39)
	{
		p->i++;
		while (para->current[p->i] != 39 && para->current[p->i] != '\0')
			p->str[p->j++] = para->current[p->i++];
		if (para->current[p->i] != 39)
			return (0);
		p->i++;
	}
	else if (para->current[p->i] == 34)
	{
		if (!current_parser3(para, p))
			return (0);
	}
	return (1);
}

char	*current_parser(t_para *para)
{
	t_parse	*p;

	p = malloc(sizeof(t_parse));
	if (!p)
		error_handler(0);
	p->i = 0;
	p->j = 0;
	p->str = malloc(sizeof(char) * ft_strlen(para->current) * 10);
	if (!p->str)
		error_handler(0);
	while (para->current[p->i] != '\0')
	{	
		if (para->current[p->i] == 39 || para->current[p->i] == 34)
		{
			if (!current_parser4(para, p))
				return (NULL);
		}
		else if (para->current[p->i] == '$')
			current_parser2(para, p);
		else
			p->str[p->j++] = para->current[p->i++];
	}
	p->str[p->j] = '\0';
	return (p->str);
}
