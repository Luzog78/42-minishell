/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:59:05 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/24 19:50:42 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	ft_printenv(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
	return (0);
}

char	**ft_add_env(char *new_var, char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (NULL);
	new_env = ft_env_cpy(env);
	new_env[i] = ft_strdup(new_var);
	new_env[i + 1] = NULL;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	return (new_env);
}

char	**ft_update_env(char *new_var, char **env)
{
	int	i;
	int	length;

	i = 0;
	while (new_var[i] && new_var[i] != '=')
		i++;
	length = i + 1;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(new_var, env[i], length) == 0)
		{
			free(env[i]);
			env[i] = ft_strdup(new_var);
			return (env);
		}
		i++;
	}
	return (env);
}

static int	var_is_here(char *var, char **env)
{
	int	i;
	int	length;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	length = i + 1;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(var, env[i], length) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_export(char *argv, t_subshell *cmds)
{
	if (!argv)
		ft_printenv(cmds->env);
	else
	{
		if (var_is_here(argv, cmds->env))
			cmds->env = ft_update_env(argv, cmds->env);
		else
			cmds->env = ft_add_env(argv, cmds->env);
		if (cmds->env == NULL)
			return (1);
	}
	return (0);
}
