/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_not_found.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 22:42:04 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/23 19:59:48 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	cmd_cmp(char *str)
{
	if (ft_strstr(str, "echo") == 4)
	{
		if (str[4] == '\0')
			return (2);
		else if (ft_strstr(str, "echo -n") == 7 && str[7] == '\0')
			return (1);
	}
	else if (ft_strstr(str, "cd "))
		return (3);
	else if (ft_strstr(str, "pwd") == 3 && str[3] == '\0')
		return (4);
	else if (ft_strstr(str, "export") == 6 && str[6] == '\0')
		return (5);
	else if (ft_strstr(str, "unset") == 5 && str[5] == '\0')
		return (6);
	else if (ft_strstr(str, "env") == 3 && str[3] == '\0')
		return (7);
	else if (ft_strstr(str, "exit") == 4 && str[4] == '\0')
		return (8);
	else if (ft_strstr(str, "cd .. "))
		return (9);
	return (0);
}

int	verif_fquote(t_para *para)
{
	char	**split;

	split = NULL;
	if (para->current[0] == 39)
		split = ft_split(para->current, 39);
	else if (para->current[0] == 34)
		split = ft_split(para->current, 34);
	else
		return (0);
	if (cmd_cmp(split[0]))
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
	return (0);
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
	printf("minishell: %s: command not found\n", out);
	g_glob.exit_status = 127;
	free(out);
}

void	cmd_not_found2(char *str)
{
	printf("minishell: %s: command not found\n", str);
	g_glob.exit_status = 127;
}
