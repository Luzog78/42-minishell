/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 00:37:18 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/08 10:18:42 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

// TO REMOVE
char	*ft_itoa(int i)
{
	char	*result;
	int		j;
	int		save;

	if (i == 0)
		return (ft_strdup("0"));
	save = i;
	j = 0;
	while (i)
	{
		i /= 10;
		j++;
	}
	result = ft_calloc(sizeof(char), (j + 1));
	if (!result)
		return (NULL);
	result[j] = '\0';
	while (j)
	{
		result[--j] = save % 10 + '0';
		save /= 10;
	}
	return (result);
}

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
	sub_str = ft_calloc(sizeof(char), (j + 1));
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

	if (str[*i] == '$' && str[*i + 1] == '?')
	{
		var = ft_itoa(g_exit);
		*result += ft_strlen(var);
		free(var);
		(*i)++;
	}
	else if (str[*i] == '$')
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
	result = ft_calloc(sizeof(char), (ft_strlen(dest) + 2));
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
	t_bool	is_empty;

	is_empty = TRUE;
	i = 0;
	int size = get_bash_string_size(str, env);
	bash_string = ft_calloc((size + 1), sizeof(char));
	if (!bash_string)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			is_empty = FALSE;
			while (str[++i] != '\'' && str[i] != '\0')
				bash_string[ft_strlen(bash_string)] = str[i];
		}
		else if (str[i] == '"')
		{
			while (str[++i] != '"' && str[i] != '\0')
			{
				if (str[i] == '$' && str[i + 1] == '?')
				{
					is_empty = FALSE;
					var = ft_itoa(g_exit);
					ft_strcat(bash_string, var);
					free(var);
					i++;
				}
				else if (str[i] == '$')
				{
					var = ft_getvar(str, &i, env);
					if (var)
					{
						is_empty = FALSE;
						ft_strcat(bash_string, var);
					}
				}
				else
				{
					is_empty = FALSE;
					bash_string[ft_strlen(bash_string)] = str[i];
				}
			}
		}
		else
		{
			if (str[i] == '$' && str[i + 1] == '?')
			{
				is_empty = FALSE;
				var = ft_itoa(g_exit);
				ft_strcat(bash_string, var);
				free(var);
				i++;
			}
			else if (str[i] == '$')
			{
				var = ft_getvar(str, &i, env);
				if (var)
				{
					is_empty = FALSE;
					ft_strcat(bash_string, var);
				}
			}
			else
			{
				is_empty = FALSE;
				bash_string[ft_strlen(bash_string)] = str[i];
			}
		}
		i++;
	}
	bash_string[get_bash_string_size(str, env)] = '\0';
	if (is_empty)
	{
		free(bash_string);
		return (NULL);
	}
	return (bash_string);
}
