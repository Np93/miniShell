/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:46:42 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/13 08:52:11 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	launch_redi(t_para *para)
{
	int	a;

	a = -1;
	while (para->split_redi[++a] != NULL)
	{
		if ((ft_strstr(para->split_redi[a], "grep") == 4
				|| ft_strstr(para->split_redi[a], "grep") == 5)
			&& (para->split_redi[a][0] == 'g'
			|| para->split_redi[a][0] == 34
			|| para->split_redi[a][0] == 39))
			para->split_redi[a] = grep_spec(para->split_redi[a], para, 0);
		else
			para->split_redi[a] = unquoter(para->split_redi[a], para);
	}
	launch_redi1(para);
}

void	launch_redi1(t_para *para)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		launch_redi2(para);
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}

void	launch_redi2(t_para *para)
{
	int	ret;
	int	i;

	i = 0;
	while (para->split_redi[i] != NULL)
		i++;
	i -= 2;
	if (check_hd(para))
		ret = redi4(para, i);
	else
		ret = choose_redi(para, i);
	if (ret != 0)
	{
		if (para->bait)
			free(para->bait);
		para->bait = ft_strdup(para->split_redi[ret]);
		cmd_not_found(para->bait);
		kill(0, SIGUSR1);
		exit(0);
	}
}

char	*unquoter(char *str, t_para *para)
{
	char	*ret;
	t_parse	*p;

	if (str[0] == '|' || str[0] == '>' || str[0] == '<')
	{
		ret = ft_strdup(str);
		free(str);
		return (ret);
	}
	p = malloc(sizeof(t_parse));
	if (!p)
		error_handler(0, para);
	p->i = 0;
	p->j = 0;
	p->str = malloc(sizeof(char) * ft_strlen(str) * 99);
	if (!p->str)
		error_handler(0, para);
	unquoter6(para, p, str);
	free(str);
	ret = ft_strdup(p->str);
	free(p->str);
	free(p);
	return (ret);
}

int	unquoter6(t_para *para, t_parse *p, char *str)
{
	while (str[p->i] != '\0')
	{
		if (str[p->i] == 39 || str[p->i] == 34)
		{
			if (!unquoter4(para, p, str))
				return (1);
		}
		else if (str[p->i] == '$')
			unquoter2(para, p, str);
		else
			if (unquoter5(p, str))
				return (unquoter5(p, str));
	}
	p->str[p->j] = '\0';
	return (0);
}
