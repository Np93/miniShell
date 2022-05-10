/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:21:38 by rmonney           #+#    #+#             */
/*   Updated: 2022/05/10 21:48:06 by rmonney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	free_exec(char **argv, char **path)
{
	int	i;

	i = -1;
	while (argv[++i] != NULL)
		free(argv[i]);
	i = -1;
	while (path[++i] != NULL)
		free(path[i]);
	free(argv);
	free(path);
}

char	**all_path_exec(t_para *para, char *end)
{
	char	**all_path;
	char	path[4097];
	int		i;
	char	*final;

	all_path = NULL;
	final = ft_strjoin("/", end);
	i = 0;
	getcwd(path, 4096);
	if (ft_getenv(para, "PATH") != NULL)
		all_path = ft_split(ft_getenv(para, "PATH"), ':');
	else
		all_path = malloc(sizeof(char *) * 992);
	while (all_path[i] != NULL)
		i++;
	all_path[i++] = ft_strdup(path);
	if (ft_strstr(end, "/"))
		all_path[i++] = ft_strdup(end);
	all_path[i] = NULL;
	i = -1;
	while (all_path[++i] != NULL)
		all_path[i] = ft_strjoin2(all_path[i], final);
	free(final);
	return (all_path);
}

int	exec_and_return2(char **all_path, char **argv, t_para *para, int i)
{
	pid_t	pid;
	int		status;

	if (access(all_path[i], F_OK) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(all_path[i], argv, para->env) == -1)
				exit(0);
			exit(1);
		}
		else
		{
			g_glob.main = 0;
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				g_glob.exit_status = WEXITSTATUS(status);
			free_exec(argv, all_path);
			g_glob.main = 1;
			return (1);
		}
	}
	else
		return (0);
}

int	exec_and_return(char **all_path, char **argv, t_para *para)
{
	int		i;
	int		ret;

	i = -1;
	while (all_path[++i] != NULL)
	{
		ret = exec_and_return2(all_path, argv, para, i);
		if (ret == 0)
			continue ;
		else
			return (1);
	}
	free_exec(argv, all_path);
	return (0);
}

int	ft_execve(t_para *para)
{
	char	**all_path;
	char	**argv;

	argv = ft_split(para->out, ' ');
	if (check_bin(argv))
		return (exec_bin(argv, para));
	if (ft_getenv(para, "PATH") == NULL)
	{
		free_malloc2(argv);
		return (-1);
	}
	ft_check_path(argv);
	all_path = all_path_exec(para, argv[0]);
	return (exec_and_return(all_path, argv, para));
}
