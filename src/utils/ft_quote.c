/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 00:37:18 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/01 02:19:11 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

/*Faire une fonction qui renvoie un char * qui a été malloc
 *Avec les ",',$ avec getenv pour $
 *La premiere quote est connecte a la quote la plus proche
 *Ex: '"""'$PWD'"""' -> """/nfs/home/..."""
*/

char	*ft_getenv(char *argv, int i)
{
	int		j;
	int		save;
	char	*sub_str;
	char	*result;

	save = i;
	j = i;
	while (argv[i] != ' ' && argv[i] != '\0')
		i++;
	j = i - j;
	sub_str = malloc(sizeof(char) * (j + 1));
	if (!sub_str)
		return (NULL);
	j = 0;
	while (argv[save] != ' ' && argv[save] != '\0')
	{
		sub_str[j] = argv[save];
		j++;
		save++;
	}
	result = getenv(sub_str);
	free(sub_str);
	return (result);
}

int	get_bash_string_size(char *str)
{
	int		result;
	int		i;
	char	*var;

	i = 0;
	result = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i] != '\0')
				result++;
		}
		else if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' && str[i] != '\0')
			{
				if (str[i] == '$')
				{
					var = ft_getenv(str, i);
					result += ft_strlen(var);
					free(var);
				}
				else
					result++;
			}
		}
		else
			result++;
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

	i = 0;
	bash_string = malloc(sizeof(char) * get_bash_string_size(str) + 1);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i] != '\0')
				bash_string = ft_addchar(bash_string, str[i++]);
		}
		else if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' && str[i] != '\0')
			{
				if (str[i] == '$')
					ft_strjoin(bash_string, ft_getenv(str, i));
				else
					bash_string = ft_addchar(bash_string, str[i]);
			}
		}
		else
			bash_string = ft_addchar(bash_string, str[i]);
		i++;
	}
	return (bash_string);
}
