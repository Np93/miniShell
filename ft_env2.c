/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 22:10:03 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/18 02:00:37 by rmonney          ###   ########.fr       */
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

void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		printf("%s\n", env[i++]);
}
