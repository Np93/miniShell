/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:24:38 by rmonney           #+#    #+#             */
/*   Updated: 2022/03/19 16:40:14 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	welcome6(void)
{
	char	*s1;
	char	*s2;
	char	*s3;
	char	*s4;
	char	*s5;

	s1 = "██  ███  ██ ██ ██ ██ ██  ███  ██";
	s2 = "██   ██  ██  █ ██ █  ██  ██   ██";
	s3 = "██    ██  ██ █ ██ █ ██  ██    ██";
	s4 = "███▄   ██  █ █ ██ █ █   █   ▄███";
	s5 = "████▄   ██ █  █  █  █  █   ▄████";
	printf("%s\n%s\n%s\n%s\n%s\n", s1, s2, s3, s4, s5);
}

void	welcome7(void)
{
	char	*s1;
	char	*s2;
	char	*s3;
	char	*s4;
	char	*s5;

	s1 = " █████   █  █ █  █ █  █   █████ ";
	s2 = "   ████   █          █   ████   ";
	s3 = "     ███                ███     ";
	s4 = "      ██                ██      ";
	s5 = "      ██                ██      ";
	printf("%s\n%s\n%s\n%s\n%s\n", s1, s2, s3, s4, s5);
}

void	welcome8(void)
{
	char	*s1;
	char	*s2;
	char	*s3;
	char	*s4;
	char	*s5;

	s1 = "      ████████▄  ▄████████      ";
	s2 = "      ████████████████████      ";
	s3 = "              ▀██▀              ";
	s4 = "                                ";
	s5 = "  ▄█████▄ ██             ██ ██  ";
	printf("%s\n%s\n%s\n%s\n%s\n", s1, s2, s3, s4, s5);
}

void	welcome9(void)
{
	char	*s1;
	char	*s2;
	char	*s3;
	char	*s4;
	char	*s5;

	s1 = "  ██   ▀▀ ██             ██ ██  ";
	s2 = "  ██▄     ██             ██ ██  ";
	s3 = "  ██████▄ █████▄ ▄█████▄ ██ ██  ";
	s4 = "   ▀█████ ██  ██ ███  ██ ██ ██  ";
	s5 = "       ██ ██  ██ ██████▀ ██ ██  ";
	printf("%s\n%s\n%s\n%s\n%s\n", s1, s2, s3, s4, s5);
}

void	welcome10(void)
{
	char	*s1;
	char	*s2;
	char	*s3;

	s1 = "  ▄▄  ▄██ ██  ██ ███  ▄▄ ██ ██  ";
	s2 = "  ▀█████▀ ██  ██ ▀█████▀ ██ ██  ";
	s3 = "───── by nhirzel & rmonney ─────";
	printf("%s\n%s\n%s\n", s1, s2, s3);
}
