/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:38:23 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/13 08:42:27 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	search_redirect5(t_para *para, int i)
{
	while (para->current[i] != '\0')
	{
		i = search_redirect3(para, i);
		if (search_redirect2(para->current, i) != -1)
		{
			para->split_redi[++para->a] = cpy_bf_redi(para->current, i);
			para->split_redi[++para->a]
				= int_to_str_redi(search_redirect2(para->current, i));
			i += (search_redirect2(para->current, i) % 2) + 1;
		}
		else
			i++;
	}
	return (i);
}

int	search_redirect4(t_para *para, int i)
{
	while (para->current[i] != '\0')
	{
		i = search_redirect3(para, i);
		if (search_redirect2(para->current, i) != -1)
		{
			para->split_redi[++para->a]
				= int_to_str_redi(search_redirect2(para->current, i));
			i += (search_redirect2(para->current, i) % 2) + 1;
			para->split_redi[++para->a] = cpy_af_redi(para->current, i);
		}
		else
			i++;
	}
	return (i);
}

char	*cpy_af_redi(char *str, int i)
{
	char	*ret;
	int		j;
	int		a;

	a = 0;
	j = i;
	while (str[j] != '<' && str[j] != '>'
		&& str[j] != '|' && str[j] != '\0')
		j++;
	ret = malloc(sizeof(char) * (j - i) * 459 + 1);
	if (!ret)
		error_handler(0, NULL);
	if (str[i] == ' ')
		i++;
	if (str[j - 1] == ' ')
		j -= 2;
	while (i <= j)
		ret[a++] = str[i++];
	ret[a] = '\0';
	return (ret);
}

char	*cpy_bf_redi(char *str, int i)
{
	char	*ret;
	int		j;
	int		a;

	a = 0;
	j = i - 1;
	while (j != 0 && str[j - 1] != '<' && str[j - 1] != '>'
		&& str[j - 1] != '|')
		j--;
	ret = malloc(sizeof(char) * (i - j) * 429 + 1 );
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
