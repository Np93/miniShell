/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:10:47 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/08 22:41:31 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*prompt_init(int argc, char **argv)
{
	char	*prompt;
	char	**split;
	int		i;

	i = 0;
	split = ft_split(getenv("PWD"), '/');
	while (split[i + 1] != NULL)
		i++;
	if (argc == 1)
		prompt = ft_strjoin("default_user@local ", split[i]);
	else
	{
		prompt = ft_strjoin(argv[1], "@local ");
		prompt = ft_strjoin(prompt, split[i]);
	}
	prompt = ft_strjoin(prompt, " % ");
	free(split);
	return (prompt);
}
