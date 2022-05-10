/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:38:23 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/10 03:32:02 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*cpy_bf_redi(char *str, int i)
{
	char	*ret;
	int		j;
	int		a;

	a = 0;
	j = i - 1;
	while (str[j - 1] != '<' && str[j - 1] != '>'
		&& str[j - 1] != '|' && j != 0)
		j--;
	ret = malloc(sizeof(char) * (i - j) + 1);
	if (!ret)
		error_handler(0, NULL);
	if (str[i - 1] == ' ')
		i--;
	if (str[j] == ' ')
		j++;
	while (j < i)
		ret[a++] = str[j++];
	ret[a] = '\0';
	return (ret);
}

char	*int_to_str_redi(int code)
{
	if (code == 0)
		return (ft_strdup(">"));
	else if (code == 1)
		return (ft_strdup(">>"));
	else if (code == 2)
		return (ft_strdup("<"));
	else if (code == 3)
		return (ft_strdup("<<"));
	else if (code == 4)
		return (ft_strdup("|"));
	else
		return (NULL);
}
