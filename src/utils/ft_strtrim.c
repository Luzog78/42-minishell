/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 03:58:22 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/12 17:39:17 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static t_bool	ft_is_whitespaces(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\0');
}

char	*ft_strtrim(char *str)
{
	char	*new_str;
	int		i;
	int		size;

	if (!str)
		return (NULL);
	while (ft_is_whitespaces(*str))
		str++;
	size = ft_strlen(str);
	while (ft_is_whitespaces(str[size - 1]))
		size--;
	new_str = ft_calloc(sizeof(char), (size + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
