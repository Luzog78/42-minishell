/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:52:40 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/24 18:51:19 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	update_path(char *path, t_subshell *cmds)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = ft_strjoin("OLDPWD=", getenv("PWD"));
	ft_export(oldpwd, cmds);
	free(oldpwd);
	pwd = ft_strjoin("PWD=", path);
	ft_export(pwd, cmds);
	free(pwd);
}

int	ft_cd(char **argv, t_subshell *cmds)
{
	char	*home;
	(void)cmds;

	if (argv[1] == NULL)
	{
		home = getenv("HOME");
		if (!home)
		{
			printf("minishell: cd: HOME not set\n");
			return (1);
		}
		if (chdir(home) == -1)
		{
			perror("minishell");
			return (1);
		}
		update_path(home, cmds);
		return (0);
	}
	if (chdir(argv[1]) == -1)
	{
		perror("minishell");
		return (1);
	}
	update_path(argv[1], cmds);
	return (0);
}
