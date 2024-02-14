/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:31:08 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/14 02:28:40 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	get_index(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '*')
		i++;
	if (!s[i])
		return (i + 1);
	return (i);
}

t_bool	ft_wildcard_allow(char *file, char *str)
{
	char	*tmpfile;
	char	*tmpwild;
	t_bool	ret;

	ret = FALSE;
	tmpfile = file;
	tmpwild = str;
	while (*tmpfile && *tmpwild)
	{
		if (*tmpwild == '*')
		{
			tmpwild++;
			if (!*tmpwild)
				return (TRUE);
			while (*tmpfile &&
				ft_strncmp(tmpfile, tmpwild, get_index(tmpwild)) != 0)
				tmpfile++;
 			if (!*tmpfile)
				return (FALSE);
			ret = TRUE;
		}
		else if (*tmpfile != *tmpwild)
			return (FALSE);
		tmpfile++;
		tmpwild++;
	}
	if (!*tmpfile && (!*tmpwild || (*tmpwild == '*' && !*(tmpwild + 1))))
		return (ret);
	return (FALSE);
}

t_bool	ft_is_wildcard(char *str)
{
	while (*str)
	{
		if (*str == '*')
			return (TRUE);
		str++;
	}
	return (FALSE);
}
