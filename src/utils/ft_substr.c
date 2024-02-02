/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 23:47:19 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/02 23:51:46 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

char	*ft_substr(char *str, int start, int len)
{
	char	*substr;
	int		i;

	substr = calloc(len + 1, sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = str[start + i];
		i++;
	}
	substr[i] = 0;
	return (substr);
}
