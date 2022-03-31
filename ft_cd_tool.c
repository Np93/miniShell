/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhirzel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 19:53:20 by nhirzel           #+#    #+#             */
/*   Updated: 2022/03/10 19:53:53 by nhirzel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if ((unsigned char *) s1 == NULL && (unsigned char *) s2 == NULL)
		return (0);
	if (n == 0)
		return (0);
	while ((i + 1) < n
		&& ((unsigned char *) s1)[i] == ((unsigned char *) s2)[i])
		i++;
	return (((unsigned char *) s1)[i] - ((unsigned char *) s2)[i]);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return (((unsigned char *) s1)[i] - ((unsigned char *) s2)[i]);
}

char	*get_env(char **env, char *envi)
{
	int		i;
	int		len;
	char	*tmp;

	envi = ft_strjoin(envi, "=");
	len = strlen(envi);
	i = 0;
	while (env[i] && ft_memcmp(envi, env[i], len))
		i++;
	if (env[i])
		tmp = env[i] + len;
	else
		tmp = 0;
	free(envi);
	return (tmp);
}
