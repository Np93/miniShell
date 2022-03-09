/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 20:12:19 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/09 20:15:33 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	error_handler(int error)
{
	if (error == 0)
	{
		printf("There was an issue with a malloc\n");
		exit(0);
	}
	if (error == 1)
		printf("It seems you didn't close your quote... \n");
}
