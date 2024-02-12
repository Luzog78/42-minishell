/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 03:58:22 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/12 04:14:59 by bcarolle         ###   ########.fr       */
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

	i = 0;
	size = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (!ft_is_whitespaces(str[i]))
			size++;
		i++;
	}
	new_str = malloc(sizeof(char) * (size + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (!ft_is_whitespaces(*str))
			new_str[i++] = *str;
		str++;
	}
	new_str[i] = '\0';
	return (new_str);
}
