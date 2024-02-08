/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:59:30 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/08 10:18:15 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	**ft_new_env(char *target, char **env, char **new_env)
{
	int	i;
	int	j;

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
	new_env = ft_calloc(sizeof(char *), i);
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

static int	is_var_here_unset(char *target, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(target, env[i], ft_strlen(target)) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_unset(char **argv, t_subshell *cmds)
{
	char	*target;
	int		i;

	if (argv[1] && argv[1][0] == '-')
	{
		ft_printf_err("minishell: unset: invalid option `%s'\n", argv[1]);
		return (2);
	}
	i = 1;
	while (argv[i])
	{
		if (argv[i] && is_var_here_unset(argv[i], cmds->env))
		{
			target = ft_get_env(argv[i], cmds->env);
			cmds->env = ft_unset_var(target, cmds->env);
			free(target);
			return (0);
		}
		i++;
	}
	return (0);
}
