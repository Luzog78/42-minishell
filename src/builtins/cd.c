/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:52:40 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/07 23:31:18 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	update_path(t_subshell *cmds)
{
	char	*pwd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", cwd);
	cmds->env = ft_update_env(pwd, cmds->env);
	free(pwd);
	free(cwd);
}

static int	ft_home_cd(t_subshell *cmds)
{
	char	*home;
	char	*oldpwd;
	char	*pwd;

	home = ft_get_value_from_env("HOME", cmds->env);
	if (!home)
	{
		printf("minishell: cd: HOME not set\n");
		return (1);
	}
	if (chdir(home) == -1)
	{
		free(home);
		perror("minishell");
		return (1);
	}
	free(home);
	pwd = ft_get_value_from_env("PWD", cmds->env);
	oldpwd = ft_strjoin("OLDPWD=", pwd);
	cmds->env = ft_update_env(oldpwd, cmds->env);
	free(pwd);
	free(oldpwd);
	update_path(cmds);
	return (0);
}

static int	ft_argv_len(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

char	*ft_get_translated_path(char *path, t_subshell *cmds)
{
	char	*home;
	char	*translated_path;

	if (path[0] == '~')
	{
		if (path[1] == '/')
		{
			home = ft_get_value_from_env("HOME", cmds->env);
			translated_path = ft_strjoin(home, path + 1);
			free(home);
			return (translated_path);
		}
	}
	else if (path[0] == '-')
	{
		translated_path = ft_get_value_from_env("OLDPWD", cmds->env);
		return (translated_path);
	}
	return (ft_strdup(path));
}

int	ft_cd(char **argv, t_subshell *cmds)
{
	char	*oldpwd;
	char	*cwd;
	char	*path;

	if (ft_argv_len(argv) > 2)
	{
		printf("minishell: cd: too many arguments\n");
		g_exit = 1;
		return (g_exit);
	}
	if (argv[1] == NULL || !ft_strcmp(argv[1], "~")
		|| !ft_strcmp(argv[1], "--"))
		return (ft_home_cd(cmds));
	path = ft_get_translated_path(argv[1], cmds);
	if (chdir(path) == -1)
	{
		perror("minishell");
		return (1);
	}
	cwd = ft_get_value_from_env("PWD", cmds->env);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	cmds->env = ft_update_env(oldpwd, cmds->env);
	free(oldpwd);
	free(path);
	free(cwd);
	update_path(cmds);
	return (g_exit);
}
