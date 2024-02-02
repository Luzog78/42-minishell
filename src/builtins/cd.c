/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:52:40 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/02 17:33:09 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	update_path(t_subshell *cmds)
{
	char	*pwd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", cwd);
	ft_export(&pwd, cmds);
	free(pwd);
	free(cwd);
}

int	ft_home_cd(t_subshell *cmds)
{
	char	*home;
	char	*oldpwd;
	char	*oldpwd_save;

	home = ft_getenv("HOME", cmds->env);
	oldpwd = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	if (!home)
	{
		printf("minishell: cd: HOME not set\n");
		return (1);
	}
	oldpwd_save = ft_strdup(oldpwd);
	ft_export(&oldpwd, cmds);
	free(oldpwd);
	if (chdir(home) == -1)
	{
		ft_export(&oldpwd_save, cmds);
		free(oldpwd_save);
		perror("minishell");
		return (1);
	}
	update_path(cmds);
	return (0);
}

int	ft_cd(char **argv, t_subshell *cmds)
{
	char	*oldpwd;
	char	*oldpwd_save;
	char	*cwd;

	if (argv[1] == NULL)
		return (ft_home_cd(cmds));
	cwd = getcwd(NULL, 0);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	free(cwd);
	oldpwd_save = ft_strdup(oldpwd);
	ft_export(&oldpwd, cmds);
	free(oldpwd);
	if (chdir(argv[1]) == -1)
	{
		ft_export(&oldpwd_save, cmds);
		free(oldpwd_save);
		perror("minishell");
		return (1);
	}
	free(oldpwd_save);
	update_path(cmds);
	return (0);
}
