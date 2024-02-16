/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 03:37:29 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/16 19:37:35 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_getvar(char *str, int *i, char **env)
{
	int		j;
	int		save;
	char	*sub_str;
	char	*result;

	(*i)++;
	save = *i;
	j = *i;
	while (ft_isalnum(str[*i]))
		(*i)++;
	j = *i - j;
	(*i)--;
	sub_str = ft_calloc(sizeof(char), (j + 1));
	if (!sub_str)
		return (NULL);
	j = 0;
	while (ft_isalnum(str[save]))
		sub_str[j++] = str[save++];
	sub_str[j] = '\0';
	result = ft_getenv(sub_str, env);
	free(sub_str);
	result = ft_strtrim(result);
	return (result);
}

void	check_dollar(int *result, int *i, char *str, char **env)
{
	char	*var;

	if (str[*i] == '$' && str[*i + 1] == '?')
	{
		var = ft_itoa(g_exit);
		*result += ft_strlen(var);
		free(var);
		(*i)++;
	}
	else if (str[*i] == '$' && ft_isalnum(str[*i + 1]))
	{
		var = ft_getvar(str, i, env);
		if (var)
		{
			*result += ft_strlen(var);
			free(var);
		}
	}
	else
		(*result)++;
}

int	get_bash_string_size(char *str, char **env, t_bool keep_quotes)
{
	int		result;
	int		i;

	i = 0;
	result = 0;
	while (str[i])
	{
		if (keep_quotes && (str[i] == '\'' || str[i] == '"'))
			result += 2;
		if (str[i] == '\'')
		{
			while (str[++i] != '\'' && str[i] != '\0')
				result++;
		}
		else if (str[i] == '"')
		{
			while (str[++i] != '"' && str[i] != '\0')
				check_dollar(&result, &i, str, env);
		}
		else
			check_dollar(&result, &i, str, env);
		i++;
	}
	return (result);
}
