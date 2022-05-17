/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 22:55:19 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/17 22:58:48 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env_malc(t_para *para, char *arg)
{
	int	i;

	i = -1;
	while (para->env_malloc[++i] != NULL)
	{
		if (ft_strstr(para->env_malloc[i], arg) == ft_strlen(arg))
			return (1);
	}
	return (0);
}

void	add_env_malc(t_para *para, char *arq)
{
	int	i;

	i = 0;
	while (para->env_malloc[i] != NULL)
	{
		if (ft_strstr(para->env_malloc[i], arg) == ft_strlen(arg))
			break ;
		i++;
	}
	if (para->env_malloc[i] == NULL)
	{
		para->env_malloc[i++] = ft_strdup(arg);
		para->env_malloc[i] = NULL;
	}
}

void	rm_env_mlc(t_para *para, char *arg)
{
	int	i;

	i = 0;
	while (para->env_malloc[i] != NULL)
	{
		if (ft_strstr(para->env_malloc[i], arg) == ft_strlen(arg))
			break ;
		i++;
	}
	if (para->env_malloc[i] != NULL)
	{
		free(para->env_malloc[i]);
		while (para->env_malloc[i + 1] != NULL)
		{
			para->env_malloc[i] = para->env_malloc[i + 1];
			i++;
		}
		para->env_malloc[i] = NULL;
	}
}
