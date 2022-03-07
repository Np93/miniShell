/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:19:29 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/07 19:24:07 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_export(t_para *para)
{
	char	*arg;
	int		i;

	i = 0;
	arg = ft_strdup(para->current + ft_strstr(para->current, "export "));
	if (!ft_strstr(arg, "="))
		return (0);
	while (para->env[i] != NULL)
		i++;
	para->env[i] = arg;
	free(arg);
	para->env[++i] = NULL;
	return (1);
}

void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		printf("%s\n", env[i++]);
}
