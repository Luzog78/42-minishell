/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:59:05 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/03 00:50:46 by bcarolle         ###   ########.fr       */
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
	char	*tmp;

	i = 0;
	while (new_var[i] && new_var[i] != '=')
		i++;
	length = i;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(new_var, env[i], length) == 0)
		{
			tmp = env[i];
			env[i] = ft_strdup(new_var);
			free(tmp);
			break ;
		}
		i++;
	}
	return (env);
}

int	var_is_here(char *var, char **env)
{
	int	i;
	int	length;

	i = 0;
	while (var[i] && var[i] != '=' && var[i] != '+')
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

int	check_var(char *var)
{
	int	i;

	i = 1;
	if (!var)
		return (1);
	if ((var[0] < 'A' || var[0] > 'Z')
		&& (var[0] < 'a' || var[0] > 'z')
		&& var[0] != '_' && var[0] != '$')
		return (0);
	while (var[i])
	{
		if (var[i] == '=' || (var[i] == '+' && var[i + 1] == '='))
			return (1);
		if ((var[i] < 'A' || var[i] > 'Z') && (var[i] < 'a' || var[i] > 'z')
			&& (var[i] < '0' || var[i] > '9') && var[i] != '_' && var[i] != '$')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_var_concat(char *var, char **env)
{
	char	*var_name;
	char	*var_value;
	char	*new_var_value;
	char	*new_var;
	int		i;

	i = 0;
	while (var[i] && var[i] != '+')
		i++;
	var_name = ft_substr(var, 0, i);
	var_value = ft_getenv(var_name, env);
	new_var_value = ft_substr(var, i + 2, ft_strlen(var) - i - 2);
	new_var = ft_strjoin(var_name, "=");
	free(var_name);
	new_var = ft_strjoin(new_var, var_value);
	new_var = ft_strjoin(new_var, new_var_value);
	free(new_var_value);
	free(var);
	return (new_var);
}

char	*ft_get_var(char **env, char *argv)
{
	char	*var;
	int		i;

	i = 0;
	var = NULL;
	if (!check_var(argv))
		return (NULL);
	while (argv[i])
	{
		if (argv[i] == '+' && argv[i + 1] == '=')
		{
			var = ft_get_bash_string(argv, env);
			var = ft_var_concat(var, env);
			break ;
		}
		i++;
	}
	if (!var)
		var = ft_get_bash_string(argv, env);
	return (var);
}

int	ft_export(char **argv, t_subshell *cmds)
{
	char	*var;

	if (!argv[0])
		ft_printenv(cmds->env);
	else
	{
		while (*argv)
		{
			var = ft_get_var(cmds->env, *argv);
			if (!check_var(var))
			{
				printf("bash: export: `%s': not a valid identifier\n", var);
				free(var);
				var = NULL;
			}
			if (var)
			{
				if (var_is_here(var, cmds->env))
					cmds->env = ft_update_env(var, cmds->env);
				else
					cmds->env = ft_add_env(var, cmds->env);
				if (cmds->env == NULL)
					return (1);
			}
			free(var);
			argv++;
		}
	}
	return (0);
}
