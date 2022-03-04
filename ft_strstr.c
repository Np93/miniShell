/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 18:21:15 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/04 18:45:28 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_strstr2(char *str, char *tofind)
{
	int	i;

	i = 0;
	while (str[i] == tofind[i])
	{
		i++;
	}
	if (tofind[i] == '\0')
		return (1);
	else
		return (0);
}

int	ft_strstr(char *str, char *tofind)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != tofind[0])
			i++;
		else
		{
			if (ft_strstr2(str + i, tofind))
				return (1);
			else
				i++;
		}
	}
	return (0);
}
/*
int main()
{
	char *str = "echo bonjour lalatina lala ";
	char *tofind = "lala";

	if (ft_strstr(str, tofind))
		printf("found one\n");
	else
		printf("nothing found\n");
	return (0);
}*/
