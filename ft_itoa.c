/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:01:22 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/23 20:40:49 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static long int	caracounter(long int n)
{
	long int	c;
	long int	i;

	c = 0;
	i = 0;
	if (n < 0)
		i = (-n);
	else
		i = n;
	while (i > 9)
	{
		i /= 10;
		c += 1;
	}
	return (c);
}

static long int	power(long int nb, int pow)
{
	long int	a;

	a = nb;
	if (pow < 0)
		return (0);
	else if (pow == 0)
		return (1);
	else
		return (a * (power(nb, (pow - 1))));
}

static char	*writer(char *s, int a, int i, long int nc)
{
	while (a >= 1)
	{
		s[i++] = (((nc / a) % 10) + 48);
		a /= 10;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_itoa(int n)
{
	int			i;
	int			a;
	char		*s;
	long int	nc;

	nc = n;
	i = 0;
	a = caracounter(nc);
	if (nc < 0)
	{
		s = malloc(sizeof(char) * (a + 3));
		if (!s)
			return (NULL);
		s[i++] = 45;
		nc *= -1;
	}
	else
	{
		s = malloc(sizeof(char) * (a + 2));
		if (!s)
			return (NULL);
	}
	a = power(10, a);
	s = writer(s, a, i, nc);
	return (s);
}
/*
int	main(void)
{
	int	n;

	n = -2147483648;
	printf("%s\n", ft_itoa(n));
	return (0);
}*/
