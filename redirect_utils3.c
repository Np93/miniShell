/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 03:26:38 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/24 03:31:59 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**all_path_exec2(t_para *para, char *end)
{
	char	**all_path;
	char	path[4097];
	int		i;
	char	*final;

	all_path = NULL;
	final = ft_strjoin("/", end);
	i = 0;
	getcwd(path, 4096);
	if (ft_getenv(para, "PATH") != NULL)
		all_path = ft_split(ft_getenv(para, "PATH"), ':');
	else
		all_path = malloc(sizeof(char *) * 992);
	while (all_path[i] != NULL)
		i++;
	all_path[i++] = ft_strdup(path);
	if (ft_strstr(end, "/"))
		all_path[i++] = ft_strdup(end);
	all_path[i] = NULL;
	i = -1;
	while (all_path[++i] != NULL)
		all_path[i] = ft_strjoin2(all_path[i], final);
	free(final);
	return (all_path);
}
