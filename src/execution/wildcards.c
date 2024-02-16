/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:31:08 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/16 16:44:16 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*ft_remove_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	char	quote;

	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (str[i] && (str[i] != '*' || quote))
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (!quote)
				quote = str[i++];
			else if (quote == str[i])
			{
				quote = 0;
				i++;
			}
			else
				new_str[j++] = str[i++];
		}
		else
			new_str[j++] = str[i++];
	}
	return (new_str);
}

static int	ft_compare_subwild(char *file, char *wild)
{
	char	*subwild;
	int		result;

	subwild = ft_remove_quotes(wild);
	if (!subwild)
		return (0);
	result = ft_strncmp(file, subwild, ft_strlen(subwild));
	free(subwild);
	return (result);
}

t_bool	ft_wildcard_allow(char *file, char *str)
{
	char	*tmpfile;
	char	*tmpwild;
	t_bool	ret;
	char	quote;

	ret = FALSE;
	tmpfile = file;
	tmpwild = str;
	quote = 0;
	while (*tmpfile && *tmpwild)
	{
		if ((*tmpwild == '\'' || *tmpwild == '"')
			&& (!quote || quote == *tmpwild))
		{
			if (!quote)
				quote = *tmpwild;
			else if (quote == *tmpwild)
				quote = 0;
			tmpwild++;
			continue ;
		}
		else if (*tmpwild == '*' && !quote)
		{
			while (*tmpwild == '*')
				tmpwild++;
			if (!*tmpwild)
				return (TRUE);
			while (*tmpfile && ft_compare_subwild(tmpfile, tmpwild) != 0)
				tmpfile++;
			if (!*tmpfile)
				return (FALSE);
			ret = TRUE;
			continue ;
		}
		else if (*tmpfile != *tmpwild)
			return (FALSE);
		tmpfile++;
		tmpwild++;
	}
	if (!*tmpfile && *tmpwild == '*')
		return (TRUE);
	if (!*tmpfile && (!*tmpwild || (*tmpwild == '*' && !*(tmpwild + 1))))
		return (ret);
	return (FALSE);
}

t_bool	ft_is_wildcard(char *str)
{
	char	quote;

	quote = 0;
	while (*str)
	{
		if (*str == '*' && !quote)
			return (TRUE);
		if (*str == '\'' || *str == '"')
		{
			if (!quote)
				quote = *str;
			else if (quote == *str)
				quote = 0;
		}
		str++;
	}
	return (FALSE);
}
