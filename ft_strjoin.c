/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:37:39 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/10 02:11:34 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char			*str;
	unsigned long	i;
	int				a;
	int				b;

	a = 0;
	b = 0;
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	i = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	while (s1[a] != '\0')
	{
		str[a] = s1[a];
		a ++;
	}
	while (s2[b] != '\0')
		str[a++] = s2[b++];
	str[a] = '\0';
	return (str);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char			*str;
	unsigned long	i;
	int				a;
	int				b;

	a = -1;
	b = 0;
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	i = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	while (s1[++a] != '\0')
		str[a] = s1[a];
	while (s2[b] != '\0')
		str[a++] = s2[b++];
	str[a] = '\0';
	free(s1);
	return (str);
}
/*
int	main(void)
{
	char	*a;
	char	*b;

	a = "judas@";
	b = "kou";
	printf("%s\n", ft_strjoin2(a, b));
	return (0);
}*/
