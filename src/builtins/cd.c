/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:52:40 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/20 16:12:33 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i])
	{
		k = i;
		while (haystack[k] == needle[j])
		{
			k++;
			j++;
			if (needle[j] == '\0')
				return ((char *)haystack + i);
		}
		j = 0;
		i++;
	}
	return (NULL);
}

static char	*ft_get_home(char **env)
{
	int		i;
	char	*home;

	i = 0;
	while (env[i] == NULL)
	{
		if (ft_strstr(env[i], "HOME="))
		{
			home = ft_strdup(env[i] + 5);
			if (!opendir(home))
			{
				perror("minishell");
				return (NULL);
			}
			return (home);
		}
		i++;
	}
	return (NULL);
}

char	*ft_get_pwd(char **env)
{
	char	*pwd;
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strcmp("PWD=", env[i]))
		{
			pwd = ft_strdup(env[i] + 4);
			if (!pwd)
				return (NULL);
			return (pwd);
		}
		i++;
	}
	return (NULL);
}

static t_bool	ft_is_home(char **argv, char **env)
{
	char	*pwd;

	pwd = ft_get_pwd(env);
	(void)argv;
	return (true);
}

static char	*ft_get_path(char **argv, char **env)
{
	char	*home;

	if (argv[1] == NULL || !ft_is_home(argv, env))
	{
		home = ft_get_home(env);
		if (!home)
			return (NULL);
		return (home);
	}
	// else if (!ft_strstr(argv[1], ".."))
	// {
	// 	path = ft_translate_path(argv, env);
	// }
	return (NULL);
}

int	ft_cd(char **argv, char **env)
{
	char	*path;

	path = ft_get_path(argv, env);
	if (!path)
		return (1);
	// ft_update_path(path, env);
	return (0);
}
