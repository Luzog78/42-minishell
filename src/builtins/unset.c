/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:59:30 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/23 18:57:07 by bcarolle         ###   ########.fr       */
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
	new_env[i] = NULL;
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
int	ft_unset(char **argv, char **env)
{
	char	*target;

	if (argv[1])
	{
		target = ft_get_env(argv[1], env);
		env = ft_unset_var(target, env);
		free(target);
		if (env == NULL)
			return (1);
	}
	return (0);
}
