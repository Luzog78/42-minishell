/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_parent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:15:13 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/07 18:29:42 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_subshell	*ft_get_parent(t_subshell *cmds)
{
	while (cmds->parent)
		cmds = cmds->parent;
	return (cmds);
}

t_subshell	*ft_get_nearest_subshell(t_subshell *cmds)
{
	while (cmds->parent)
	{
		if (cmds->type == SUBSHELL)
			return (cmds);
		cmds = cmds->parent;
	}
	return (cmds);
}
