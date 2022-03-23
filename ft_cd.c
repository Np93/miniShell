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

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if ((unsigned char *) s1 == NULL && (unsigned char *) s2 == NULL)
		return (0);
	if (n == 0)
		return (0);
	while ((i + 1) < n
		&& ((unsigned char *) s1)[i] == ((unsigned char *) s2)[i])
		i++;
	return (((unsigned char *) s1)[i] - ((unsigned char *) s2)[i]);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return (((unsigned char *) s1)[i] - ((unsigned char *) s2)[i]);
}

char	*get_env(char **env, char *envi)
{
	int		i;
	int		len;
	char	*tmp;

	envi = ft_strjoin(envi, "=");
	len = strlen(envi);
	i = 0;
	while (env[i] && ft_memcmp(envi, env[i], len))
		i++;
	if (env[i])
		tmp = env[i] + len;
	else
		tmp = 0;
	free(envi);
	return (tmp);
}

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
	while (str[i])
	{
		str[i] = str[i + 2];
		i++;
	}
	str[0] = '/';
}

void	ft_cd(t_para *para, int cmd)
{
	char 	temp_pwd[4097];
	char 	*path;

	magic(para->out);
	getcwd(temp_pwd, 4096);
	if (cmd == 3)
	 	path = ft_strdup("..");
	if (cmd == 9)
		path = ft_strjoin(get_env(para->env, "PWD"), para->out);
	if (chdir(path) == 0)
	{
		update_oldpwd(para->env, temp_pwd);
		update_pwd(para->env);	
	}
}
