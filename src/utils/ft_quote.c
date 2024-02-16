/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 00:37:18 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/16 11:20:00 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*Faire une fonction qui renvoie un char * qui a été malloc
 *Avec les " ' $ avec getenv pour $
 *La premiere quote est connecte a la quote la plus proche
 *Ex: '"""'$PWD'"""' -> """/nfs/home/..."""
*/

void	ft_double_quote(char *str, char *bash_string, int *i, char **env)
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
	else if (str[*i] == '$' && str[*i + 1] != '\0' && str[*i + 1] != '\''
		&& !ft_is_whitespace(str[*i + 1]) && str[*i + 1] != '"')
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

void	ft_no_quote(char *str, char *bash_string, int *i, char **env)
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
	else if (str[*i] == '$' && str[*i + 1] != '\0'
		&& ft_is_whitespace(str[*i + 1]) == FALSE)
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

char	*ft_get_bash_string(char *str, char **env)
{
	int		i;
	char	*bash_string;

	i = -1;
	bash_string = ft_calloc((get_bash_string_size(str, env) + 1), sizeof(char));
	if (!bash_string)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == '\'')
			while (str[++i] != '\'' && str[i] != '\0')
				bash_string[ft_strlen(bash_string)] = str[i];
		else if (str[i] == '"')
			while (str[++i] != '"' && str[i] != '\0')
				ft_double_quote(str, bash_string, &i, env);
		else
			ft_no_quote(str, bash_string, &i, env);
	}
	bash_string[get_bash_string_size(str, env)] = '\0';
	if (bash_string && bash_string[0] == '\0')
	{
		free(bash_string);
		return (NULL);
	}
	return (bash_string);
}
