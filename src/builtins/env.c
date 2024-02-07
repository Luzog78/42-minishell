/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:59:49 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/07 02:55:30 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(char **argv, char **env)
{
	int	i;

	i = 0;
	if (argv[1] && argv[1][0] == '-')
	{
		write(2, "env: invalid option\n", 20);
		return (125);
	}
	else if (argv[1] && argv[1][0] != '-')
	{
		write(2, "env: too many arguments\n", 25);
		return (127);
	}
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
