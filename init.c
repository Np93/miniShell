/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:10:47 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/03 23:42:33 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*prompt_init(int argc, char **argv)
{
	char	*prompt;

	if (argc == 1)
		prompt = "default_user@local_minishell % ";
	else
		prompt = ft_strjoin(argv[1], "@local_minishell % ");
	return (prompt);
}

void	free_malloc_cd(char *str, t_para *para)
{
	if (str != NULL && !ft_strstr(para->current, "cd"))
		free(str);
}

void	free_malloc2(char **sp)
{
	int	i;

	i = -1;
	while (sp[++i] != NULL)
		free(sp[i]);
	free(sp);
}

void	free_malloc(char *str)
{
	if (str != NULL)
		free(str);
}
