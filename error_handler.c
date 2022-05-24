/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 20:12:19 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/24 01:46:06 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	error_unset(t_para *para)
{
	int		i;
	char	**sp;

	i = -1;
	sp = ft_split(para->out, ' ');
	while (sp[++i] != NULL)
	{
		if (ft_strstr(sp[i], "="))
			printf("minishell: unset: `%s': not a valid identifier\n 🐚", sp[i]);
	}
	free_malloc2(sp);
}

void	error_handler2(int error, t_para *para)
{
	if (error == 7)
		printf("Error : %s 🐚\n", strerror(errno));
	if (error == 8)
		error_unset(para);
	if (error == 9)
		printf("minishell: %s: No such file or directory\n 🐚", para->bait);
	if (error == 10)
		printf("minishell: syntax error near unexpected token `newline' 🐚\n");
}

void	error_handler(int error, t_para *para)
{
	if (error == 0)
	{
		printf("There was an issue with a malloc\n 🐚");
		exit(0);
	}
	if (error == 1)
		printf("It seems you didn't close your quote... 🐚\n");
	if (error == 2)
		printf("We don't handle the ';' sorry mate ¯\\_(ツ)_/¯ 🐚\n");
	if (error == 3)
		cmd_not_found2(para->bait);
	if (error == 4)
		printf("Usage : ./minishell ([username]) 🐚\n");
	if (error == 5)
	{
		printf("Fd is non TTY 🐚\n");
		exit(0);
	}
	if (error == 6)
	{
		printf("An error occured with the termios structure\n 🐚");
		exit(0);
	}
	error_handler2(error, para);
}
