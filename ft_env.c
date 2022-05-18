/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:19:29 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/18 02:20:48 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_export3(t_para *para, char *arg)
{
	int	j;

	j = 0;
	while (para->env[j] != NULL)
	{
		if (ft_strstr(para->env[j], arg) == ft_strlen(arg))
			break ;
		j++;
	}
	return (j);
}

void	ft_export2(t_para *para, char *arg, char **split, int i)
{
	int	j;

	while (split[i] != NULL)
	{
		if (ft_strstr(split[i], "="))
		{
			arg = cpy_bf_equal(split[i]);
			j = ft_export3(para, arg);
			if (para->env[j] != NULL)
			{
				if (is_env_malc(para, arg))
					free(para->env[j]);
				para->env[j] = ft_strdup(split[i]);
				add_env_malc(para, arg);
			}
			else
			{
				para->env[j++] = ft_strdup(split[i]);
				para->env[j] = NULL;
				add_env_malc(para, arg);
			}
			free(arg);
		}
		i++;
	}
}

int	ft_export(t_para *para)
{
	char	*arg;
	char	**split;

	if (para->out[6] == '\0')
		return (empty_export(para));
	arg = ft_strdup(para->current + ft_strstr(para->current, "export "));
	split = ft_split(arg, ' ');
	free(arg);
	ft_export2(para, arg, split, 0);
	free_malloc2(split);
	return (1);
}

void	ft_unset2(t_para *para, char *arg)
{
	int	i;

	i = 0;
	while (ft_strstr(para->env[i], arg) != (ft_strlen(arg)))
		i++;
	if (para->env[i] == NULL)
		return ;
	if (is_env_malc(para, arg))
		free(para->env[i]);
	rm_env_malc(para, arg);
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

	i = 0;
	if (ft_strstr(para->out, "="))
	{
		error_handler(8, para);
		return (0);
	}
	arg = ft_strdup(para->out + ft_strstr(para->out, "unset "));
	split = ft_split(arg, ' ');
	while (split[i] != NULL)
	{
		if (ft_getenv(para, split[i]) == NULL)
			i++;
		else
		{
			ft_unset2(para, split[i]);
			i++;
		}
	}
	(free(arg), free_malloc2(split));
	return (1);
}
