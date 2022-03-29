/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:26:16 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/29 21:45:18 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*    34 = "    39 = '    */

int	search_redirection2(char *str, int i)
{
	if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (2);
		else
			return (1);
	}
	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return (4);
		else
			return (3);
	}
	if (str[i] == '|')
		return (5);
	return (0);
}

int	search_redirection(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34)
		{
			i++;
			while (str[i] != 34)
				i++;
		}
		if (str[i] == 39)
		{
			i++;
			while (str[i] != 39)
				i++;
		}
		if (search_redirection2(str, i))
			return (search_redirection2(str, i));
		else
			i++;
	}
	return (0);
}

void	exec_redirection(t_para *para, int redi)
{
	(void)para;
	if (redi == 1)
		printf("redirection = >\n");
	if (redi == 2)
		printf("redirection = >>\n");
	if (redi == 3)
		printf("redirection = <\n");
	if (redi == 4)
		printf("redirection = <<\n");
	if (redi == 5)
		printf("redirection = |\n");
}

void	ft_readline2(t_para *para)
{
	int	redi;

	if (*para->current != '\0')
	{
		redi = search_redirection(para->current);
		if (redi)
			exec_redirection(para, redi);
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
