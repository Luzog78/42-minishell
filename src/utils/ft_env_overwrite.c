/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_overwrite.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 20:08:43 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/25 11:14:25 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

char	**ft_env_owrite(char **new_env, char **env)
{
	int	i = 0;

	while(env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	env = ft_env_cpy(new_env);
	return (env);
}