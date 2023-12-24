/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 03:56:05 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/13 05:42:47 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	hd_in_out(t_para *para, t_hd *hd)
{
	int	i;

	i = 0;
	while (para->split_redi[i] != NULL)
	{
		if (ft_strstr(para->split_redi[i], ">"))
		{
			if (ft_strcmp(para->split_redi[i], ">") == 0)
				hd->fdout = open(para->split_redi[i + 1],
						O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
			else if (ft_strcmp(para->split_redi[i], ">>") == 0)
				hd->fdout = open(para->split_redi[i + 1],
						O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
		}
		if (ft_strcmp(para->split_redi[i], "<") == 0 && 0 <= hd->fdin)
		{
			if (open(para->split_redi[i + 1], O_RDONLY) == -1)
				hd->fdin = (i + 1) * -1;
			else
				hd->fdin = i + 1;
		}
		i++;
	}
	if (ft_strstr(para->split_redi[i - 2], "<<") && 0 < hd->fdin)
		hd->fdin = 0;
}

int	check_hd(t_para *para)
{
	int	i;

	i = 0;
	while (para->split_redi[i] != NULL)
	{
		if (ft_strstr(para->split_redi[i], "<<"))
			return (1);
		i++;
	}
	return (0);
}

void	init_hd(t_hd *hd)
{
	hd->limit = malloc(sizeof(char *) * 888);
	hd->argv = malloc(sizeof(char *) * 555);
	hd->fdt = open("tmp", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	hd->argv[0] = ft_strdup("cat");
	hd->argv[2] = NULL;
	hd->j = 0;
	hd->line = "";
	hd->fdin = 0;
	hd->fdout = 0;
}

int	set_limit_and_red(t_hd *hd, t_para *para, int i)
{
	while (0 <= i)
	{
		if (ft_strcmp(para->split_redi[i], "<<") == 0)
			hd->limit[hd->j++] = ft_strdup(para->split_redi[i + 1]);
		if (0 < i)
			i--;
		else
			break ;
	}
	if (ft_strcmp(para->split_redi[0], "<<") != 0)
		i++;
	while (ft_strstr(para->split_redi[i], "|"))
		i += 2;
	hd->limit[hd->j] = NULL;
	hd->j--;
	hd_in_out(para, hd);
	return (i);
}

void	readline_hd(t_hd *hd)
{
	while (0 <= hd->j)
	{
		while (ft_strcmp(hd->line, hd->limit[hd->j]) != 0)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			hd->line = readline("> ");
			if (hd->j == 0 && ft_strcmp(hd->line, hd->limit[hd->j]) != 0)
			{
				write(hd->fdt, hd->line, ft_strlen(hd->line));
				write(hd->fdt, "\n", 1);
			}
		}
		hd->j--;
	}
}
