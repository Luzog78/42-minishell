/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:59:30 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/25 12:18:06 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	**ft_new_env(char *target, char **env, char **new_env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strcmp(env[i], target) != 0)
		{
			new_env[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
	return (new_env);
}

char	**ft_unset_var(char *target, char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return (NULL);
	new_env = ft_new_env(target, env, new_env);
	new_env[i - 1] = NULL;
	i = 0;
	return (new_env);
}

char	*ft_get_env(char *target, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(target, env[i], ft_strlen(target)) == 0)
			return (ft_strdup(env[i]));
		i++;
	}
	return (NULL);
}

static int	var_is_here(char *var, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(var, env[i], ft_strlen(var)) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_unset(char **argv, t_subshell *cmds)
{
	char	*target;

	if (argv[1] && var_is_here(argv[1], cmds->env))
	{
		target = ft_get_env(argv[1], cmds->env);
		cmds->env = ft_unset_var(target, cmds->env);
		free(target);
		if (cmds->env == NULL)
			return (1);
	}
	return (0);
}
