/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_realloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 02:33:56 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 02:34:14 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_args_realloc(char ***args, char *str)
{
	char	**new;
	int		i;

	i = 0;
	while (*args && (*args)[i])
		i++;
	new = ft_calloc(sizeof(char *), (i + 2));
	if (!new)
		return ;
	i = 0;
	while (*args && (*args)[i])
	{
		new[i] = ft_strdup((*args)[i]);
		i++;
	}
	new[i] = ft_strdup(str);
	i = 0;
	while (*args && (*args)[i])
	{
		free((*args)[i]);
		i++;
	}
	free(*args);
	*args = new;
}
