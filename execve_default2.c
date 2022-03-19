/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_default2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:50:46 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/19 18:52:32 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*last_path(char *arg)
{
	char	**path;
	char	*ret;
	int		i;

	i = 0;
	path = ft_split(arg, '/');
	while (path[i + 1] != NULL)
		i++;
	ret = ft_strdup(path[i]);
	free(path);
	return (ret);
}

void	ft_check_path(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		if (ft_strstr(argv[i], "/"))
		{
			argv[i] = last_path(argv[i]);
			i++;
		}
		else
			i++;
	}
}
