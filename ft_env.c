/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:19:29 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/09 22:20:56 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_export(t_para *para)
{
	char	*arg;
	int		i;
	int		j;
	char	**split;

	i = 0;
	j = 0;
	arg = ft_strdup(para->current + ft_strstr(para->current, "export "));
	split = ft_split(arg, ' ');
	while (para->env[j] != NULL)
		j++;
	while (split[i] != NULL)
	{
		if (!ft_strstr(split[i], "="))
			i++;
		else
			para->env[j++] = ft_strdup(split[i++]);
	}
	free(arg);
	free(split);
	para->env[j] = NULL;
	return (1);
}

void	ft_unset2(t_para *para, char *arg)
{
	int	i;

	i = 0;
	while (!ft_strstr(para->env[i], arg))
		i++;
	while (para->env[i + 1] != NULL)
	{
		para->env[i] = para->env[i + 1];
		i++;
	}
	para->env[i] = NULL;
}

int	ft_unset(t_para *para)
{
	char	*arg;
	char	**split;
	int		i;
	int		j;

	i = 0;
	arg = ft_strdup(para->current + ft_strstr(para->current, "unset "));
	split = ft_split(arg, ' ');
	while (split[i] != NULL)
	{
		j = 0;
		if (getenv(split[i]) == NULL)
			i++;
		else
		{
			ft_unset2(para, split[i]);
			i++;
		}
	}
	free(arg);
	free(split);
	return (1);
}

void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		printf("%s\n", env[i++]);
}

char	*ft_getenv(t_para *para, char *var)
{
	int	i;

	i = 0;
	while (para->env[i] != NULL)
	{
		if (ft_strstr(para->env[i], var) == ft_strlen(var))
			return (&(*(para->env[i] + ft_strlen(var) + 1)));
		else
			i++;
	}
	return (NULL);
}
