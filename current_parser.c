/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   current_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 18:55:51 by rmonney           #+#    #+#             */
/*   Updated: 2022/04/12 23:04:33 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*  92 = \  //  39 = '  //  34 = "  */

char	*get_dollar(char *current, int i, t_para *para)
{
	char	arg[999];
	int		j;
	char	*ret;

	j = 0;
	if (current[i] == '?')
		return (ft_itoa(g_glob.exit_status));
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
	if (para->current[p->i] == '?')
		p->i++;
	else
	{
		while (para->current[p->i] != ' ' && para->current[p->i] != 39
			&& para->current[p->i] != 34 && para->current[p->i] != '\0')
			p->i++;
	}
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
		else if (para->current[p->i] == 92)
			current_parser7(para, p);
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

int	current_parser(t_para *para)
{
	t_parse	*p;
	int		err;

	if ((ft_strstr(para->current, "grep") == 4
			|| ft_strstr(para->current, "grep") == 5)
		&& (para->current[0] == 'g' || para->current[0] == 34
			|| para->current[0] == 39))
	{
		para->out = grep_spec(para->current, para, 1);
		return (0);
	}
	p = malloc(sizeof(t_parse));
	p->str = malloc(sizeof(char) * (ft_strlen(para->current) * 99));
	if (!p || !p->str)
		error_handler(0, para);
	p->i = 0;
	p->j = 0;
	err = current_parser6(para, p);
	para->out = ft_strdup(p->str);
	free(p);
	if (err != 0)
		return (err);
	if (verif_fquote(para, para->current))
		return (3);
	return (0);
}
