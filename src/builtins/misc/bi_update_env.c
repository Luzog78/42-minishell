/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_update_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:36:55 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/14 03:37:07 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	**bi_update_env(char *new_var, char **env)
{
	int		i;
	int		length;
	char	*tmp;

	i = 0;
	while (new_var[i] && new_var[i] != '=')
		i++;
	length = i;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(new_var, env[i], length) == 0)
		{
			tmp = env[i];
			env[i] = ft_strdup(new_var);
			free(tmp);
			break ;
		}
		i++;
	}
	return (env);
}
