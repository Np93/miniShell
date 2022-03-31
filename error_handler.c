/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 20:12:19 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/29 16:39:15 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void
{
	if (error == 0)
	{
		printf("There was an issue with a malloc\n");
		exit(0);
	}
	if (error == 1)
		printf("It seems you didn't close your quote... \n");
	if (error == 2)
		printf("We don't handle the ';' sorry mate ¯\\_(ツ)_/¯ \n");
	if (error == 3)
		cmd_not_found2(para->bait);
	if (error == 4)
		printf("Usage : ./minishell ([username])\n");
	if (error == 5)
	{
		printf("Fd is non TTY\n");
		exit(0);
	}
	if (error == 6)
	{
		printf("An error occured with the termios structure\n");
		exit(0);
	}
	if (error == 7)
		printf("cd Error loser :)\n");
}
