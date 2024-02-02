/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 00:37:18 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/02 23:55:05 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

/*Faire une fonction qui renvoie un char * qui a été malloc
 *Avec les " ' $ avec getenv pour $
 *La premiere quote est connecte a la quote la plus proche
 *Ex: '"""'$PWD'"""' -> """/nfs/home/..."""
*/

char	*ft_getvar(char *str, int *i, char **env)
{
	int		j;
	int		save;
	char	*sub_str;
	char	*result;

	(*i)++;
	save = *i;
	j = *i;
	while (str[*i] != ' ' && str[*i] != '\0' && str[*i] != '\\' && str[*i] != '+'
		&& str[*i] != '"' && str[*i] != '\'' && str[*i] != '$' && str[*i] != '=')
		(*i)++;
	j = *i - j;
	(*i)--;
	sub_str = malloc(sizeof(char) * (j + 1));
	if (!sub_str)
		return (NULL);
	j = 0;
	while (str[save] != ' ' && str[save] != '\0' && str[save] != '\\'
		&& str[save] != '"' && str[save] != '\'' && str[save] != '$'
		&& str[save] != '=' && str[save] != '+')
		sub_str[j++] = str[save++];
	sub_str[j] = '\0';
	result = ft_getenv(sub_str, env);
	free(sub_str);
	return (result);
}

void	check_dollar(int *result, int *i, char *str, char **env)
{
	char	*var;

	if (str[*i] == '$')
	{
		var = ft_getvar(str, i, env);
		if (var)
			*result += ft_strlen(var);
	}
	else
		(*result)++;
}
int	get_bash_string_size(char *str, char **env)
{
	int		result;
	int		i;

	i = 0;
	result = 0;
	while (str[i])
	{
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

char	*ft_addchar(char *dest, char character)
{
	int		i;
	char	*result;

	i = 0;
	result = malloc(sizeof(char) * (ft_strlen(dest) + 2));
	if (!result)
		return (NULL);
	while (dest[i])
	{
		result[i] = dest[i];
		i++;
	}
	result[i] = character;
	result[i + 1] = '\0';
	free(dest);
	return (result);
}

char	*ft_get_bash_string(char *str, char **env)
{
	int		i;
	char	*bash_string;
	char	*var;

	i = 0;
	bash_string = calloc(sizeof(char), get_bash_string_size(str, env) + 1);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			while (str[++i] != '\'' && str[i] != '\0')
				bash_string[ft_strlen(bash_string)] = str[i];
		}
		else if (str[i] == '"')
		{
			while (str[++i] != '"' && str[i] != '\0')
			{
				if (str[i] == '$')
				{
					var = ft_getvar(str, &i, env);
					if (var)
						ft_strcat(bash_string, var);
				}
				else
					bash_string[ft_strlen(bash_string)] = str[i];
			}
		}
		else
		{
			if (str[i] == '$')
			{
				var = ft_getvar(str, &i, env);
				if (var)
					ft_strcat(bash_string, var);
			}
			else
				bash_string[ft_strlen(bash_string)] = str[i];
		}
		i++;
	}
	bash_string[get_bash_string_size(str, env)] = '\0';
	return (bash_string);
}
