/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhirzel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 19:04:11 by nhirzel           #+#    #+#             */
/*   Updated: 2021/10/21 19:42:21 by nhirzel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ss;

	ss = (unsigned char *) s;
	i = 0;
	if (n == 0)
		return ;
	while (i < n)
	{
		ss[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	long_mem;
	void	*resul;

	long_mem = count * size;
	resul = malloc(long_mem);
	if (resul == NULL)
		return (0);
	ft_bzero(resul, long_mem);
	return (resul);
}
