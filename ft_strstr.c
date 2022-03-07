/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 18:21:15 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/07 15:18:03 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strstr2(char *str, char *tofind)
{
	int	i;

	i = 0;
	while (str[i] == tofind[i] && str[i] != '\0')
		i++;
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
				return (i + ft_strlen(tofind));
			else
				i++;
		}
	}
	return (0);
}
/*
int main()
{
	char *str = "lalatina lala ";
	char *tofind = "lala ";

	if (ft_strstr(str, tofind))
		printf("found one in position %d\n", ft_strstr(str, tofind));
	else
		printf("nothing found\n");
	return (0);
}*/
