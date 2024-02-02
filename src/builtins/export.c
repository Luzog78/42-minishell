/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:59:05 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/02 21:54:19 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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

char	**ft_sort_env(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[j])
		{
			if (ft_strncmp(env[i], env[j], ft_strlen(env[i])) < 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (env);
}

static void	ft_printenv(char **env)
{
	int		i;
	char	**sorted_env;

	i = 0;
	while (env[i])
		i++;
	sorted_env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	ft_arr_char_cpy(env, sorted_env);
	sorted_env = ft_sort_env(sorted_env);
	while (sorted_env[i])
	{
		printf("declare -x %s\n", sorted_env[i]);
		i++;
	}
	sorted_env[i] = NULL;
	i = 0;
	while (sorted_env[i])
	{
		free(sorted_env[i]);
		i++;
	}
	free(sorted_env);
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

int	var_is_here(char *var, char **env)
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

char	*var_concatenation(char *var)
{
	int		i;
	char	*new_var;
	int		j;

	i = 0;
	while (var[i])
	{
		if (var[i] == '+' && var[i + 1] == '=')
		{
			i = 0;
			j = 0;
			new_var = malloc(sizeof(char) * ft_strlen(var));
			while (var[i])
			{
				if (var[i] != '+')
					new_var[j++] = var[i];
				i++;
			}
			new_var[j] = '\0';
			free(var);
			var = new_var;
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_cat_var(char **env, char *argv)
{
	int		i;
	int		length;
	char	*var;

	i = 0;
	while (argv[i] && argv[i] != '=')
		i++;
	length = i;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], argv, length) == 0)
		{
			var = ft_strjoin(env[i], argv + length);
			return (var);
		}
		i++;
	}
	return (NULL);
}

int	ft_export(char **argv, t_subshell *cmds)
{
	char	*var_concatened;

	if (!argv[0])
		ft_printenv(cmds->env);
	else
	{
		while (*argv)
		{
			if (var_concatenation(*argv) == 1)
			{
				var_concatened = ft_cat_var(cmds->env, *argv);
				free(*argv);
				*argv = var_concatened;
			}
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
