/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:48:40 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/10 03:32:07 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	welcome(void)
{
	welcome1();
	welcome2();
	welcome3();
	welcome4();
	welcome5();
	welcome6();
	welcome7();
	welcome8();
	welcome9();
	welcome10();
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

void	init_para(t_para **para, char **env)
{
	(*para) = (t_para *)malloc(sizeof(t_para) * 99);
	(*para)->split_redi = malloc(sizeof(char *) * 995);
	(*para)->out = malloc(sizeof(char) * 999);
	(*para)->env = env;
	(*para)->env_cpy = env_cpy(*para, env);
	(*para)->cd = 0;
	g_glob.exit_status = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_para	*para;

	if (argc > 2)
	{
		error_handler(4, NULL);
		return (0);
	}
	welcome();
	g_glob.main = 1;
	ft_signal();
	init_para(&para, env);
	ft_termios(para);
	para->prompt = prompt_init(argc, argv);
	while (1)
	{
		if (g_glob.main == 1)
		{
			ft_readline(para);
			if (current_parser(para))
				g_glob.exit_status = 1;
		}
	}
	exit(0);
	return (0);
}
