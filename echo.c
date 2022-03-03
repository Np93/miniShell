/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 20:49:11 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/03 20:54:53 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_echo(int mode, char *str)
{
	while (*str == ' ')
		str++;
	if (mode == 1)
		printf("%s", str);
	else if (mode == 2)
		printf("%s\n", str);
}
