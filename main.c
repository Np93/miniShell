/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:48:40 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/04 18:45:44 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	search_fct(char *str)
{
	if (*str == 'e' && *(str + 1) == 'c' && *(str + 2) == 'h'
		&& *(str + 3) == 'o' && *(str + 4) == ' ')
	{
		if (*(str + 5) == '-' && *(str + 6) == 'n')
			return (1);
		else
			return (2);
	}
	if (*str == 'e' && *(str + 1) == 'x' && *(str + 2) == 'i'
		&& *(str + 3) == 't' && *(str + 4) == '\0')
		return (8);
	return (0);
}

void	do_fct(int cmd, char *current)
{
	if (cmd == 1)
		ft_echo(1, current + 8);
	else if (cmd == 2)
		ft_echo(2, current + 5);
	else if (cmd == 8)
		exit(0);
}

int	main(void)
{
	g_para = *(t_para *)malloc(sizeof(t_para));
	g_para.prompt = "Waiting on a new command : ";
	while (1)
	{
		g_para.current = readline(g_para.prompt);
		while (*g_para.current == ' ')
			g_para.current++;
		g_para.cmd = search_fct(g_para.current);
		if (g_para.cmd == 0)
			printf("%s: command not found\n", g_para.current);
		else
			do_fct(g_para.cmd, g_para.current);
		add_history(g_para.current);
	}
	return (0);
}
