/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:21:19 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/02 17:21:27 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

char	*ft_getenv(char *name, char **env)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(name, env[i], len) == 0)
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}
