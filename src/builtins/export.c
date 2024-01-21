/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:59:05 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/21 20:59:17 by bcarolle         ###   ########.fr       */
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
	new_env = ft_env_cpy(env);
	new_env[i] = ft_strdup(new_var);
	new_env[i + 1] = NULL;
	return (new_env);
}

int	ft_export(char **argv, char **env)
{
	if (!argv[1])
		ft_printenv(env);
	else
	{
		ft_add_env(argv[1], env);
	}
	return (0);
}
