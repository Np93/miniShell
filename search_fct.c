/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_fct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:51:16 by rmonney           #+#    #+#             */
/*   Updated: 2022/04/12 00:17:56 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	search_fct(char *str)
{
	if (ft_strstr(str, "echo") == 4 && str[4] == ' ')
	{
		if (ft_strstr(str, "echo -n") == 7 && str[7] == ' ')
			return (1);
		else
			return (2);
	}
	else if (ft_strstr(str, "cd") == 2)
		return (3);
	else if (ft_strstr(str, "pwd") == 3)
		return (4);
	else if (ft_strstr(str, "export") == 6 && str[6] == ' ')
		return (5);
	else if (ft_strstr(str, "unset") == 5 && str[5] == ' ')
		return (6);
	else if (ft_strstr(str, "env") == 3)
		return (7);
	else if (ft_strstr(str, "exit") == 4)
		return (8);
	return (0);
}

void	do_fct(int cmd, t_para *para)
{
	if (cmd == 0)
	{
		if (ft_execve(para) == 0)
			cmd_not_found(para->out);
		return ;
	}
	else if (cmd == 1)
		ft_echo(1, para->out + 8);
	else if (cmd == 2)
		ft_echo(2, para->out + 5);
	else if (cmd == 3)
		ft_cd(para);
	else if (cmd == 4)
		ft_pwd(para);
	else if (cmd == 5)
		ft_export(para);
	else if (cmd == 6)
		ft_unset(para);
	else if (cmd == 7)
		ft_env(para->env);
	else if (cmd == 8)
		exit(0);
	g_glob.exit_status = 0;
}
