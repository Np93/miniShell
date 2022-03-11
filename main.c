/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:48:40 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/11 18:01:54 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

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

void	ft_readline(int argc, char **argv, char **env, t_para *para)
{
	(void)env;
	rl_on_new_line();
	para->prompt = prompt_init(argc, argv);
	para->current = readline(para->prompt);
//	if (STDIN_FILENO == EOF)
//		exit(0);
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

int	main(int argc, char **argv, char **env)
{
	t_para	*para;

	if (argc > 2)
		return (0);
	ft_signal();
	init_para(&para, argv, env);
	while (1)
	{
		ft_readline(argc, argv, env, para);
		/*
		rl_on_new_line();
		para->prompt = prompt_init(argc, argv);
		para->current = readline(para->prompt);
		if (STDIN_FILENO == NULL)
			exit(0);
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
		*/
	}
	return (0);
}
