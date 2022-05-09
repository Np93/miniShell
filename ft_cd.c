/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhirzel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 19:53:20 by nhirzel           #+#    #+#             */
/*   Updated: 2022/05/10 01:04:12 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	update_oldpwd(char **env, char *oldpwd, t_para *para)
{
	int		i;
	char	*temp;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			temp = ft_strjoin("OLDPWD=", oldpwd);
			if (para->cd == 1)
				free(env[i]);
			env[i] = ft_strdup(temp);
			free(temp);
			return ;
		}
		i++;
	}
	if (env[i] == NULL)
	{
		temp = ft_strjoin("OLDPWD=", oldpwd);
		env[i++] = ft_strdup(temp);
		free(temp);
	}
}

void	update_pwd(char **env, t_para *para)
{
	int		i;
	char	*temp;
	char	pwd[4097];

	i = 0;
	getcwd(pwd, 4096);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			temp = ft_strjoin("PWD=", pwd);
			if (para->cd == 1)
				free(env[i]);
			env[i] = ft_strdup(temp);
			free(temp);
			return ;
		}
		i++;
	}
	if (env[i] == NULL)
	{
		temp = ft_strjoin("PWD=", pwd);
		env[i++] = ft_strdup(temp);
		free(temp);
	}
}

int	magic(t_para *para)
{
	int	i;
	int	count;

	i = 2;
	count = 0;
	if (para->out[2] == '\0')
		return (1);
	else if (para->out[2] == ' ')
	{
		while (para->out[i] != '\0' && (para->out[i] == ' '
				|| para->out[i] == '~'))
		{
			if (para->out[i] == '~')
				count++;
			i++;
		}
		if (count <= 1 && ft_strlen(para->out) == i)
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
		path = ft_strdup("/Users");
	else
		path = path_is(para->out);
	if (chdir(path) == 0)
	{
		update_oldpwd(para->env, temp_pwd, para);
		update_pwd(para->env, para);
		para->cd = 1;
	}
	else
		error_handler(7, para);
	free(path);
}

char	*path_is(char *para_out)
{
	int		i;
	char	*path;

	i = 0;
	while (para_out[i] != ' ')
		i++;
	while (para_out[i] == ' ')
		i++;
	path = ft_strdup(para_out + i);
	return (path);
}
//		printf("Error : %s\n", strerror(errno));
//		//a la place de error_handler7 si veut erreur sys exacte
