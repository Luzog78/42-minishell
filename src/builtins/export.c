/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:59:05 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/24 18:00:36 by bcarolle         ###   ########.fr       */
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
	// while (env[i])
	// {
	// 	free(env[i]);
	// 	i++;
	// }
	// free(env);
	return (new_env);
}

int	ft_export(char **argv, t_subshell *cmds)
{
	if (!argv[1])
		ft_printenv(cmds->env);
	else
	{
		cmds->env = ft_add_env(argv[1], cmds->env);
		if (cmds->env == NULL)
			return (1);
	}
	return (0);
}
