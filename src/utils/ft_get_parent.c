/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_parent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:15:13 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/11 20:28:54 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_subshell	*ft_get_parent(t_subshell *cmds)
{
	while (cmds->parent)
		cmds = cmds->parent;
	return (cmds);
}
