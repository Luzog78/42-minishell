/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:59:49 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/08 03:22:14 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(char **argv, char **env)
{
	int	i;

	i = 0;
	if (argv[1] && argv[1][0] == '-')
	{
		ft_printf_err("env: invalid option `%s'\n", argv[1]);
		return (125);
	}
	else if (argv[1] && argv[1][0] != '-')
	{
		ft_print_err("env: too many arguments\n");
		return (127);
	}
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
