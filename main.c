/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:48:40 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/07 18:46:04 by rmonney          ###   ########.fr       */
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

void	do_fct(int cmd, t_para *para)
{
	if (cmd == 0)
		printf("%s: command not found\n", para->current);
	else if (cmd == 1)
		ft_echo(1, para->current + 8);
	else if (cmd == 2)
		ft_echo(2, para->current + 5);
	else if (cmd == 4)
		ft_pwd(para);
	else if (cmd == 7)
		ft_env(para->env);
	else if (cmd == 8)
		exit(0);
}

char	**cpy_env(char **env)
{
	int		len;
	int		i;
	char	**cpy;

	len = 0;
	while (env[len])
		len++;
	if (!(cpy = (char **)ft_calloc(sizeof(char *), (len + 1))))
		return (0);
	i = 0;
	while (i < len)
	{
		cpy[i] = ft_strdup(env[i]);
		i++;
	}
	return (cpy);
}

void	init_para(t_para **para, char **argv, char **env)
{
	(*para) = (t_para *)malloc(sizeof(t_para));
	(*para)->argv = argv;
	(*para)->env = cpy_env(env);
}

int	main(int argc, char **argv, char **env)
{
	t_para	*para;

	if (argc != 1)
		return (0);
	init_para(&para, argv, env);
	para->prompt = "Judas@minishell % ";
	while (1)
	{
		para->current = readline(para->prompt);
		while (*para->current == ' ')
			para->current++;
		para->cmd = search_fct(para->current);
		do_fct(para->cmd, para);
		add_history(para->current);
	}
	return (0);
}
