/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_is_var_in_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:35:50 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/14 03:35:58 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	bi_is_var_in_env(char *var, char **env)
{
	int	i;
	int	length;

	i = 0;
	while (var[i] && var[i] != '=' && var[i] != '+')
		i++;
	length = i + 1;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(var, env[i], length) == 0)
			return (1);
		i++;
	}
	return (0);
}
