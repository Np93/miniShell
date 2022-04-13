/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhirzel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 19:53:20 by nhirzel           #+#    #+#             */
/*   Updated: 2022/04/12 00:16:49 by rmonney          ###   ########.fr       */
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

int	magic(t_para *para)
{
	int	i;
	int	count;

	i = 2;
	count = 0;
	if (para->out[3] == '\0')
		return (1);
	else if (ft_strncmp(para->out, "cd ~", 4) == 0)
		return (1);
	else if (para->out[3] == ' ' && para->out[4] != '~')
	{
		while (para->out[i] != '\0' && (para->out[i] == ' ' || para->out[i] == '~'))
		{
			if (para->out[i] == '~')
				count++;
			i++;
		}
		if (count == 1)
			return (1);
	}
	return (0);
}

void	ft_cd(t_para *para)
{
	char	temp_pwd[4097];
	char	*path;

	getcwd(temp_pwd, 4096);
	if (magic(para) == 1)
		path = ("/Users");
	else
	{
		while (*para->out != ' ')
			para->out++;
		if (*para->out == ' ')
		{
			while (*para->out == ' ')
				para->out++;
		}
		path = para->out;
	}
	if (chdir(path) == 0)
	{
		update_oldpwd(para->env, temp_pwd);
		update_pwd(para->env);
	}
	else
//		printf("Error : %s\n", strerror(errno));
		error_handler(7, para);
}
