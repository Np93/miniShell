/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:26:16 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/25 18:05:01 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	last_cmd3(t_para *para, char *arg)
{
	int	j;

	j = 0;
	while (para->env[j] != NULL)
	{
		if (ft_strstr(para->env[j], arg)
			&& para->env[j][ft_strlen(arg)] == '=')
		{
			break ;
		}
		j++;
	}
	return (j);
}

void	last_cmd2(t_para *para, char *all)
{
	int		j;
	char	*arg;

	arg = cpy_bf_equal(all);
	j = last_cmd3(para, arg);
	if (para->env[j] != NULL)
	{
		if (is_env_malc(para, arg))
			free(para->env[j]);
		para->env[j] = ft_strdup(all);
		add_env_malc(para, arg);
	}
	else
	{
		para->env[j++] = ft_strdup(all);
		para->env[j] = NULL;
		add_env_malc(para, arg);
	}
	free(arg);
}

void	last_cmd(t_para *para, int i)
{
	int		a;
	char	*tmp;

	if (i == 1)
	{
		tmp = ft_strdup("_= ");
		last_cmd2(para, tmp);
	}
	else
	{
		a = 0;
		while (para->out[a] != '\0')
			a++;
		while (para->out[a] != ' ' && a != 0)
			a--;
		if (a != 0)
			a++;
		tmp = ft_strjoin("_=", (para->out + a));
		last_cmd2(para, tmp);
	}
	free(tmp);
}

void	ft_readline2(t_para *para)
{
	para->i = 0;
	if (*para->current != '\0')
	{
		if (current_parser(para))
			error_handler(current_parser(para), para);
		else
		{
			if (search_redirect(para))
			{
				launch_redi(para);
				para->i = 1;
				ft_freeee_split_redi(para);
			}
			else
			{
				if (para->i != 1)
				{
					para->cmd = search_fct(para->out);
					do_fct(para->cmd, para);
				}
			}
		}
		last_cmd(para, para->i);
	}
}

void	ft_readline(t_para *para)
{
	if (g_glob.main == 1)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
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
			exit(0);
	}
}
