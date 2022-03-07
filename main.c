/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:48:40 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/07 14:50:09 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	search_fct(char *str)
{
	if (ft_strstr(str, "echo "))
	{
		if (ft_strstr(str, "echo -n "))
			return (1);
		else
			return (2);
	}
	else if (ft_strstr(str, "cd "))
		return (3);
	else if (ft_strstr(str, "pwd"))
		return (4);
	else if (ft_strstr(str, "export "))
		return (5);
	else if (ft_strstr(str, "unset "))
		return (6);
	else if (ft_strstr(str, "env"))
		return (7);
	else if (ft_strstr(str, "exit"))
		return (8);
	return (0);
}

void	do_fct(int cmd, char *current)
{
	if (cmd == 0)
		printf("%s: command not found\n", current);
	else if (cmd == 1)
		ft_echo(1, current + 8);
	else if (cmd == 2)
		ft_echo(2, current + 5);
	else if (cmd == 8)
		exit(0);
}

int	main(void)
{
	g_para = *(t_para *)malloc(sizeof(t_para));
	g_para.prompt = "Judas@minishell % ";
	while (1)
	{
		g_para.current = readline(g_para.prompt);
		while (*g_para.current == ' ')
			g_para.current++;
		g_para.cmd = search_fct(g_para.current);
		do_fct(g_para.cmd, g_para.current);
		add_history(g_para.current);
	}
	return (0);
}
