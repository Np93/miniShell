/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 18:21:15 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/13 07:20:21 by rmonney          ###   ########.fr       */
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

int	ft_strstr2(char *str, char *tofind, int i)
{
	int	j;

	j = 0;
	while (str[i] == tofind[j] && str[i] != '\0')
	{
		i++;
		j++;
	}
	if (tofind[j] == '\0')
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
			if (ft_strstr2(str, tofind, i))
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
	char *str = "jesus";
	char *tofind = "suasd";

	if (ft_strstr(str, tofind))
		printf("found one in position %d\n", ft_strstr(str, tofind));
	else
		printf("nothing found\n");
	return (0);
}*/
