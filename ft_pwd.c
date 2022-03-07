/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:38:44 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/07 18:43:28 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_pwd(t_para *para)
{
	int	i;

	i = 0;
	while (!ft_strstr(para->env[i], "PWD="))
		i++;
	printf("%s\n", para->env[i] + ft_strstr(para->env[i], "PWD="));
}
