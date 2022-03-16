/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_fct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:51:16 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/16 19:01:09 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
/*
int	ft_execve(t_para *para)
{
	int		ret;
	char	*path;
	char	**argv;
	char	**envp;

	argv = malloc(sizeof(char *) * 10);
	ret = 0;
	if (para->current[0] == 'l' && para->current[1] == 's')
	{
//		path = ft_getenv(para, "PWD");
		path = "/bin/bash";
		argv[0] = path;
		argv[1] = "-c";
		argv[2] = "./minishell";
		argv[3] = NULL;
		envp = para->env;
		ret = execve(path, argv, envp);
		if (ret == -1)
		{
			printf("echec critique\n");
		}
		else
			return (1);
	}
	return (0);
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
	else if (ft_strstr(str, "cd .."))
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
	else if (ft_strstr(str, "cd "))
		return (9);
	return (0);
}
*/
void	do_fct(int cmd, t_para *para)
{
	if (cmd == 0)
	{
//		if (ft_execve(para) == 0)
			cmd_not_found(para->out);
	}
	else if (cmd == 1)
		ft_echo(1, para->out + 8);
	else if (cmd == 2)
		ft_echo(2, para->out + 5);
	else if (cmd == 3)
		ft_cd(para, cmd);
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
	else if (cmd == 9)
		ft_cd(para, cmd);
}
