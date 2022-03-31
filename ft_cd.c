/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhirzel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 19:53:20 by nhirzel           #+#    #+#             */
/*   Updated: 2022/03/10 19:53:53 by rmonney          ###   ########.fr       */
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

void	magic(char *str)
{
	int	i;

	i = 0;
	if (str[3] != '/')
	{
		while (str[i])
		{
			str[i] = str[i + 2];
			i++;
		}
		str[0] = '/';
	}
	if (str[3] == '/')
	{
		while (str[i])
		{
			str[i] = str[i + 3];
			i++;
		}
	}
}

void	ft_cd(t_para *para, int cmd)
{
	char 	temp_pwd[4097];
	char 	*path;

	getcwd(temp_pwd, 4096);
	if (cmd == 3)
	 	path = ft_strdup("..");
	if (cmd == 9)
	{
		magic(para->out);
		if (ft_strstr(para->out, "/Users"))
			path = para->out;
		else
			path = ft_strjoin(get_env(para->env, "PWD"), para->out);
	}
	if (chdir(path) == 0)
	{
		update_oldpwd(para->env, temp_pwd);
		update_pwd(para->env);	
	}
	else
		error_handler(7, para);
}
