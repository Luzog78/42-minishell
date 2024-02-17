/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 02:30:06 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 04:05:56 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static t_bool	is_alphanum(char c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (TRUE);
	return (FALSE);
}

char	*ft_tolower(const char *str)
{
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (str[++i])
		if (is_alphanum(str[i]))
			j++;
	new = ft_calloc(sizeof(char), j + 1);
	if (!new)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			new[j++] = str[i] + 32;
		else if ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= '0' && str[i] <= '9'))
			new[j++] = str[i];
	}
	return (new);
}
