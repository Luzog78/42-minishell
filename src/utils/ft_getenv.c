/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:21:19 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/12 17:26:31 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_getenv(char *name, char **env)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(name, env[i], len) == 0 && env[i][len] == '=')
		{
			if (*(env[i] + len + 1) == '\0')
				return (NULL);
			return (env[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}
