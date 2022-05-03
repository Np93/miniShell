/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:10:47 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/03 18:28:19 by rmonney          ###   ########.fr       */
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

void	free_malloc(char *str)
{
	if (str)
		free(str);
}

void	free_malloc2(char **sp)
{
	if (sp)
		free(sp);
}
