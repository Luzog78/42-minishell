/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 00:37:18 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/01 20:29:25 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

/*Faire une fonction qui renvoie un char * qui a été malloc
 *Avec les " ' $ avec getenv pour $
 *La premiere quote est connecte a la quote la plus proche
 *Ex: '"""'$PWD'"""' -> """/nfs/home/..."""
*/

char	*ft_getenv(char *str, int *i)
{
	int		j;
	int		save;
	char	*sub_str;
	char	*result;

	(*i)++;
	save = *i;
	j = *i;
	while (str[*i] != ' ' && str[*i] != '\0' && str[*i] != '\\'
		&& str[*i] != '"' && str[*i] != '\'' && str[*i] != '$')
		(*i)++;
	j = *i - j;
	(*i)--;
	sub_str = malloc(sizeof(char) * (j + 1));
	if (!sub_str)
		return (NULL);
	j = 0;
	while (str[save] != ' ' && str[save] != '\0' && str[save] != '\\'
		&& str[save] != '"' && str[save] != '\'' && str[save] != '$')
		sub_str[j++] = str[save++];
	sub_str[j] = '\0';
	result = getenv(sub_str);
	free(sub_str);
	return (result);
}

void	check_dollar(int *result, int *i, char *str)
{
	char	*var;

	if (str[*i] == '$')
	{
		var = ft_getenv(str, i);
		if (var)
			*result += ft_strlen(var);
	}
	else
		(*result)++;
}
int	get_bash_string_size(char *str)
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
				check_dollar(&result, &i, str);
		}
		else
			check_dollar(&result, &i, str);
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

char	*ft_get_bash_string(char *str)
{
	int		i;
	char	*bash_string;
	char	*var;

	i = 0;
	bash_string = calloc(sizeof(char), get_bash_string_size(str) + 1);
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
					var = ft_getenv(str, &i);
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
				var = ft_getenv(str, &i);
				if (var)
					ft_strcat(bash_string, var);
			}
			else
				bash_string[ft_strlen(bash_string)] = str[i];
		}
		i++;
	}
	bash_string[get_bash_string_size(str)] = '\0';
	return (bash_string);
}
