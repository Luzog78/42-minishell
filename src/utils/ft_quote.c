/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 00:37:18 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/17 03:22:57 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	ft_double_quote(char *str, char *bash_string, int *i, char **env)
{
	char	*var;

	var = NULL;
	if (str[*i] == '$' && str[*i + 1] == '?')
	{
		var = ft_itoa(g_exit);
		ft_strcat(bash_string, var);
		free(var);
		(*i)++;
	}
	else if (str[*i] == '$' && ft_isalnum(str[*i + 1]))
	{
		var = ft_getvar(str, i, env);
		if (var)
		{
			ft_strcat(bash_string, var);
			free(var);
		}
	}
	else
		bash_string[ft_strlen(bash_string)] = str[*i];
}

static void	ft_no_quote(char *str, char *bash_string, int *i, char **env)
{
	char	*var;

	var = NULL;
	if (str[*i] == '$' && str[*i + 1] == '?')
	{
		var = ft_itoa(g_exit);
		ft_strcat(bash_string, var);
		free(var);
		(*i)++;
	}
	else if (str[*i] == '$' && (ft_isalnum(str[*i + 1])
			|| str[*i + 1] == '\'' || str[*i + 1] == '\"'))
	{
		var = ft_getvar(str, i, env);
		if (var)
		{
			ft_strcat(bash_string, var);
			free(var);
		}
	}
	else
		bash_string[ft_strlen(bash_string)] = str[*i];
}

char	*ft_get_bash_string(char *str, char **env, t_bool keep_quotes)
{
	int		i;
	char	*bash_string;
	int 	size;

	i = -1;
	size = get_bash_string_size(str, env, keep_quotes);
	bash_string = ft_calloc(size + 1, sizeof(char));
	if (!bash_string)
		return (NULL);
	while (str[++i])
	{
		if (keep_quotes && (str[i] == '\'' || str[i] == '"'))
			bash_string[ft_strlen(bash_string)] = str[i];
		if (str[i] == '\'')
			while (str[++i] != '\'' && str[i] != '\0')
				bash_string[ft_strlen(bash_string)] = str[i];
		else if (str[i] == '"')
			while (str[++i] != '"' && str[i] != '\0')
				ft_double_quote(str, bash_string, &i, env);
		else
			ft_no_quote(str, bash_string, &i, env);
		if (keep_quotes && (str[i] == '\'' || str[i] == '"'))
			bash_string[ft_strlen(bash_string)] = str[i];
	}
	bash_string[size] = '\0';
	if (bash_string && bash_string[0] == '\0')
	{
		free(bash_string);
		return (NULL);
	}
	return (bash_string);
}
