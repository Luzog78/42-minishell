/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:59:05 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/02 17:39:08 by bcarolle         ###   ########.fr       */
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

void	ft_arr_char_cpy(char **src, char **dst)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = ft_strdup(src[i]);
		i++;
	}
	dst[i] = NULL;
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
	ft_arr_char_cpy(env, new_env);
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
	int		i;
	int		length;
	char	*value;
	int		mode;

	i = -1;
	mode = 0;
	while (new_var[++i] && mode == 0)
	{
		if (new_var[i] == '=')
			mode = 1;
		if (new_var[i] == '+' && new_var[i + 1] == '=')
			mode = 2;
	}
	length = i + 1;
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(new_var, env[i], length) == 0)
		{
			free(env[i]);
			if (mode == 1 || mode == 0)
				env[i] = ft_get_bash_string(new_var, env);
			else if (mode == 2)
			{
				value = ft_get_bash_string(new_var + length, env);
				env[i] = ft_strjoin(env[i], value);
				free(value);
				value = NULL;
			}
			return (env);
		}
	}
	return (env);
}

static int	var_is_here(char *var, char **env)
{
	int	i;
	int	length;
	int	save;

	i = 0;
	save = 0;
	while (var[i] && var[i] != '=' && var[i] != '+')
		i++;
	length = i + 1;
	if (var[i] == '+')
		var[i] = '=';
	save = i;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(var, env[i], length) == 0)
		{
			if (save != 0)
				var[save] = '+';
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_export(char **argv, t_subshell *cmds)
{
	if (!argv[0])
		ft_printenv(cmds->env);
	else
	{
		while (*argv)
		{
			if (var_is_here(*argv, cmds->env))
				cmds->env = ft_update_env(*argv, cmds->env);
			else
				cmds->env = ft_add_env(*argv, cmds->env);
			if (cmds->env == NULL)
				return (1);
			argv++;
		}
	}
	return (0);
}
