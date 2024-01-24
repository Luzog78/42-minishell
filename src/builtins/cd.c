/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:52:40 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/24 19:35:11 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	update_path(char *path, t_subshell *cmds)
{
	char	*pwd;
	(void)path;

	pwd = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", pwd);
	ft_export(pwd, cmds);
	free(pwd);
}

int	ft_home_cd(t_subshell *cmds)
{
	char	*home;
	char	*oldpwd;
	char	*oldpwd_save;

	home = getenv("HOME");
	oldpwd = ft_strjoin("OLDPWD=", getenv("PWD"));
	if (!home)
	{
		printf("minishell: cd: HOME not set\n");
		return (1);
	}
	oldpwd_save = ft_strdup(oldpwd);
	ft_export(oldpwd, cmds);
	free(oldpwd);
	if (chdir(home) == -1)
	{
		ft_export(oldpwd_save, cmds);
		free(oldpwd_save);
		perror("minishell");
		return (1);
	}
	update_path(home, cmds);
	return (0);
}

int	ft_cd(char **argv, t_subshell *cmds)
{
	char	*oldpwd;
	char	*oldpwd_save;

	if (argv[1] == NULL)
		return (ft_home_cd(cmds));
	oldpwd = ft_strjoin("OLDPWD=", getenv("PWD"));
	oldpwd_save = ft_strdup(oldpwd);
	ft_export(oldpwd, cmds);
	free(oldpwd);
	if (chdir(argv[1]) == -1)
	{
		ft_export(oldpwd_save, cmds);
		free(oldpwd_save);
		perror("minishell");
		return (1);
	}
	update_path(argv[1], cmds);
	return (0);
}
