/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:52:40 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/17 02:58:47 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	update_path(t_subshell *cmds)
{
	char	*pwd;
	char	*cwd;
	char	*value_envp;

	cwd = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", cwd);
	value_envp = ft_get_value_from_env("PWD", cmds->env);
	if (!value_envp)
		cmds->env = bi_add_env(pwd, cmds->env);
	else
	{
		cmds->env = bi_update_env(pwd, cmds->env);
		free(value_envp);
	}
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
		ft_print_err("minishell: cd: HOME not set\n");
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
	cmds->env = bi_update_env(oldpwd, cmds->env);
	free(pwd);
	free(oldpwd);
	update_path(cmds);
	return (0);
}

static char	*ft_get_translated_path(char *path, t_subshell *cmds)
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
		if (!translated_path)
		{
			ft_print_err("minishell: cd: OLDPWD not set\n");
			g_exit = 1;
			return (NULL);
		}
		return (translated_path);
	}
	return (ft_strdup(path));
}

static int	ft_change_dir(char *path, char *cwd, t_subshell *cmds)
{
	char	*oldpwd;

	if (!cwd)
		oldpwd = ft_strdup("OLDPWD");
	else
		oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (chdir(path) == -1)
	{
		free(oldpwd);
		free(cwd);
		free(path);
		perror("minishell");
		return (1);
	}
	cmds->env = bi_update_env(oldpwd, cmds->env);
	free(oldpwd);
	free(path);
	free(cwd);
	return (0);
}

int	ft_cd(char **argv, t_subshell *cmds)
{
	char	*cwd;
	char	*path;

	if (argv[0] && argv[1] && argv[2])
	{
		ft_print_err("minishell: cd: too many arguments\n");
		g_exit = 1;
		return (g_exit);
	}
	if (argv[1] == NULL || !ft_strcmp(argv[1], "~")
		|| !ft_strcmp(argv[1], "--"))
		return (ft_home_cd(cmds));
	path = ft_get_translated_path(argv[1], cmds);
	cwd = ft_get_value_from_env("PWD", cmds->env);
	g_exit = ft_change_dir(path, cwd, cmds);
	update_path(cmds);
	return (g_exit);
}
