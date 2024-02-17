/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_ignore_case.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 02:29:34 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 02:29:43 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_strcmp_ignore_case(const char *s1, const char *s2)
{
	const char	*str1;
	const char	*str2;
	size_t		i;
	int			result;

	result = 0;
	str1 = ft_tolower(s1);
	str2 = ft_tolower(s2);
	if (str1 && str2)
	{
		i = 0;
		while (str1[i] && str2[i] && str1[i] == str2[i])
			i++;
		result = (unsigned char)str1[i] - (unsigned char)str2[i];
	}
	free((char *)str1);
	free((char *)str2);
	return (result);
}
