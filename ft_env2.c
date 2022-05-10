/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 22:10:03 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/10 03:21:40 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	empty_export(t_para *para)
{
	int		i;
	int		alpha;
	char	**sp;

	alpha = 48;
	while (alpha <= 122)
	{
		i = -1;
		while (para->env[++i] != NULL)
		{
			if (para->env[i][0] == alpha)
			{
				sp = ft_split(para->env[i], '=');
				printf("declare -x %s=\"%s\"\n", sp[0], sp[1]);
				free_malloc2(sp);
			}
		}
		alpha++;
	}
	return (1);
}

char	**env_cpy(t_para *para, char **env)
{
	char	**env_cpy;
	int		i;

	env_cpy = malloc(sizeof(char *) * 998);
	if (!env_cpy)
		error_handler(0, para);
	i = -1;
	while (env[++i] != NULL)
		env_cpy[i] = ft_strdup(env[i]);
	env_cpy[i] = NULL;
	return (env_cpy);
}

int	env_cmp(char *arg, t_para *para)
{
	int	i;

	if (ft_strstr(arg, "PWD"))
	{
		if (ft_getenv(para, arg) && para->cd == 1)
			return (0);
	}
	i = -1;
	while (para->env_cpy[++i] != NULL)
	{
		if (ft_strstr(para->env_cpy[i], arg) == ft_strlen(arg))
			return (1);
	}
	return (0);
}
