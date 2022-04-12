/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhirzel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 19:53:20 by nhirzel           #+#    #+#             */
/*   Updated: 2022/04/12 23:10:35 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	update_oldpwd(char **env, char *oldpwd)
{
	int		i;
	char	*temp;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			temp = ft_strjoin("OLDPWD=", oldpwd);
			env[i] = temp;
		}
		i++;
	}
}

static void	update_pwd(char **env)
{
	int		i;
	char	*temp;
	char	pwd[4097];

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			getcwd(pwd, 4096);
			temp = ft_strjoin("PWD=", pwd);
			env[i] = temp;
		}
		i++;
	}
}

void	ft_cd(t_para *para)
{
	char	temp_pwd[4097];
	char	*path;

	getcwd(temp_pwd, 4096);
	if (para->out[3] == '\0')
		path = ("/Users");
	else
	{
		while (*para->out != ' ')
			para->out++;
		para->out++;
		path = para->out;
	}
	if (chdir(path) == 0)
	{
		update_oldpwd(para->env, temp_pwd);
		update_pwd(para->env);
	}
	else
		error_handler(7, para);
}
//		printf("Error : %s\n", strerror(errno));
//		//a la place de error_handler7 si veut erreur sys exacte
