/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_not_found.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 22:42:04 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/11 23:47:24 by nhirzel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	cmd_cmp(char *str)
{
	if (ft_strstr(str, "echo "))
	{
		if (ft_strstr(str, "echo -n") == 7 && str[7] == '\0')
			return (0);
		else
			return (1);
	}
	if (ft_strstr(str, "echo -n "))
		return (1);
	if (ft_strstr(str, "cd "))
		return (1);
	if (ft_strstr(str, "pwd "))
		return (1);
	if (ft_strstr(str, "export "))
		return (1);
	if (ft_strstr(str, "unset "))
		return (1);
	if (ft_strstr(str, "env "))
		return (1);
	if (ft_strstr(str, "exit "))
		return (1);
	if (ft_strstr(str, "cd .. "))
		return (1);
	return (0);
}

/*     34 = "    39 = '    */

int	verif_fquote(t_para *para, char *str)
{
	char	**split;

	split = NULL;
	if (str[0] == 39)
		split = ft_split(str, 39);
	else if (str[0] == 34)
		split = ft_split(str, 34);
	else
		return (0);
	if (!cmd_cmp(split[0]))
	{
		free(split);
		return (0);
	}
	else
	{
		para->bait = ft_strdup(split[0]);
		free(split);
		return (1);
	}
}

void	cmd_not_found(char *str)
{
	int		i;
	char	*out;

	i = 0;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	out = malloc(sizeof(char) * i + 1);
	if (!out)
		error_handler(0, NULL);
	i = 0;
	while (str[i] != ' ' && str[i] != '\0')
	{
		out[i] = str[i];
		i++;
	}
	out[i] = '\0';
	printf("minishell: %s: command not found🐚\n", out);
	g_glob.exit_status = 127;
	free(out);
}

void	cmd_not_found2(char *str)
{
	printf("minishell: %s: command not found🐚\n", str);
	g_glob.exit_status = 127;
}
