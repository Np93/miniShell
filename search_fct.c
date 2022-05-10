/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_fct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:51:16 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/10 02:58:36 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	no_path(char *str)
{
	int		i;
	char	*out;

	i = 0;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	out = malloc(sizeof(char) * i + 1);
	if (!out)
		error_handler(0, NULL);
	i = 0;
	while (str[i] != ' ' && str[i] != '\0')
	{
		out[i] = str[i];
		i++;
	}
	out[i] = '\0';
	printf("minishell: %s: no such file or directory\n", out);
	g_glob.exit_status = 127;
	free(out);
}

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
	else if (ft_strstr(str, "export") == 6)
		return (5);
	else if (ft_strstr(str, "unset") == 5)
		return (6);
	else if (ft_strstr(str, "env") == 3)
		return (7);
	else if (ft_strstr(str, "exit") == 4)
		return (8);
	else if (ft_strstr(str, "grep") == 4)
		return (9);
	return (0);
}

void	do_fct(int cmd, t_para *para)
{
	if (cmd == 0)
	{
		if (ft_execve(para) == 0)
			cmd_not_found(para->out);
		else if (ft_execve(para) == -1)
			no_path(para->out);
		return ;
	}
	else if (cmd == 1)
		ft_echo(1, para->out + 8);
	else if (cmd == 2)
		ft_echo(2, para->out + 5);
	else if (cmd == 3)
		ft_cd(para);
	else if (cmd == 4)
		ft_pwd();
	else if (cmd == 5)
		ft_export(para);
	else if (cmd == 6)
		ft_unset(para);
	else if (cmd == 7)
		ft_env(para->env);
	else if (cmd == 8)
		exit(0);
	else if (cmd == 9)
		grepr(para);
	g_glob.exit_status = 0;
}
