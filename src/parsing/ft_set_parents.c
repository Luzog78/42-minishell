/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_parents.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:34:21 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/13 10:35:12 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_set_parents(t_subshell *subshell)
{
	t_subshell	*tmp;

	tmp = subshell->cmds;
	while (tmp)
	{
		tmp->parent = subshell;
		ft_set_parents(tmp);
		tmp = tmp->next;
	}
}
