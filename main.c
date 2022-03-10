/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:48:40 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/10 23:03:24 by rmonney          ###   ########.fr       */
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
	else if (ft_strstr(str, "cd "))
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
	else if (ft_strstr(str, "cd .. "))
		return (9);
	return (0);
}

void	do_fct(int cmd, t_para *para)
{
	if (cmd == 0)
		cmd_not_found(para->out);
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

char	**cpy_env(char **env)
{
	int		len;
	int		i;
	char	**cpy;

	len = 0;
	while (env[len])
		len++;
	cpy = (char **)ft_calloc(sizeof(char *), (len + 1));
	if (!cpy)
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
	(*para)->env = env;
}

int	main(int argc, char **argv, char **env)
{
	t_para	*para;

	if (argc > 2)
		return (0);
	init_para(&para, argv, env);
	while (1)
	{
		rl_on_new_line();
		para->prompt = prompt_init(argc, argv);
		para->current = readline(para->prompt);
		add_history(para->current);
		while (*para->current == ' ')
			para->current++;
		if (current_parser(para))
			error_handler(current_parser(para), para);
		else
		{
			para->cmd = search_fct(para->out);
			do_fct(para->cmd, para);
		}
		rl_redisplay();
	}
	return (0);
}
