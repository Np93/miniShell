/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:26:16 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/30 23:18:28 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*cpy_bf_redi(char *str, int i)
{
	char	*ret;
	int		j;
	int		a;

	a = 0;
	j = i - 1;
	while (str[j - 1] != '<' && str[j - 1] != '>'
		&& str[j - 1] != '|' && j != 0)
		j--;
	ret = malloc(sizeof(char) * (i - j) + 1);
	if (!ret)
		error_handler(0, NULL);
	if (str[i - 1] == ' ')
		i--;
	if (str[j] == ' ')
		j++;
	while (j < i)
	{
		ret[a++] = str[j++];
	}
	ret[a] = '\0';
	return (ret);
}

char	*int_to_str_redi(int code)
{
	if (code == 0)
		return (">");
	else if (code == 1)
		return (">>");
	else if (code == 2)
		return ("<");
	else if (code == 3)
		return ("<<");
	else if (code == 4)
		return ("|");
	else
		return (NULL);
}

void	ft_readline2(t_para *para)
{
	if (*para->current != '\0')
	{
		if (search_redirect(para))
			launch_redirect(para);
		else
		{
			if (current_parser(para))
				error_handler(current_parser(para), para);
			else
			{
				para->cmd = search_fct(para->out);
				do_fct(para->cmd, para);
			}
		}
	}
}

void	ft_readline(t_para *para)
{
	para->current = readline(para->prompt);
	if (para->current != NULL)
	{
		if (para->current[0])
		{
			add_history(para->current);
			while (*para->current == ' ')
				para->current++;
			ft_readline2(para);
		}
	}
	else
		exit (0);
}
