/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:38:12 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/23 20:29:50 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static long int	whatsign(const char *str)
{
	long int	a;
	long int	sign;

	a = 0;
	sign = 0;
	while (str[a] == ' ' || str[a] == '\t' || str[a] == '\n'
		|| str [a] == '\v' || str[a] == '\f' || str[a] == '\r')
		a ++;
	if (str[a] == 43)
		sign = 1;
	else if (47 < str[a] && str[a] <= 57)
		sign = 1;
	else if (str[a] == 45)
		sign = -1;
	else
		sign = 0;
	if (str[a] == 43 || str[a] == 45)
	{
		a++;
		if (str[a] <= 47 || 57 < str[a])
			sign = 0;
	}
	return (sign);
}

static long int	valuec(const char *str)
{
	long int	a;
	long int	c;

	a = 0;
	c = 1;
	while (str[a] <= 47 || 57 < str[a])
		a ++;
	while (47 < str[a] && str[a] <= 57)
	{
		a ++;
		c *= 10;
	}
	return (c);
}

int	ft_atoi(char *str)
{
	long int	nb;
	long int	a;
	long int	c;
	long int	b;
	long int	sign;

	a = 0;
	nb = 0;
	b = 0;
	sign = whatsign(str);
	c = valuec(str);
	while (str[a] <= 47 || 57 < str[a])
		a ++;
	b = a;
	while (47 < str[a] && str[a] <= 57)
		a ++;
	while (b <= a)
	{
		nb += ((str[b] - 48) * (c / 10));
		c /= 10;
		b ++;
	}
	nb *= sign;
	return (nb);
}
/*
int	main(void)
{
	char	*w;

	w = "99999";
	printf("%d <-- ft_atoi\n", ft_atoi(w));
	printf("%d <-- atoi\n", atoi(w));
}*/
