/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:19:29 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/07 20:08:30 by rmonney          ###   ########.fr       */
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

int	ft_unset(t_para* para)
{
	char	*arg;
	int		i;
	i = 0;
	arg = ft_strdup(para->current + ft_strstr(para->current, "unset "));
	while (!ft_strstr(para->env[i], arg) && para->env[i] != NULL)
		i++;
	if (para->env[i] == NULL)
		return (0);
	if (ft_strstr(para->env[i], "=") != ft_strlen(arg))
		return (0);
	while (para->env[i + 1] != NULL)
	{
		para->env[i] = NULL;
		para->env[i] = ft_strdup(para->env[i + 1]);
		i++;
	}
	para->env[i] = NULL;
	return (1);
}

void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		printf("%s\n", env[i++]);
}
