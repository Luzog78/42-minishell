/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_prevs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:35:39 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/13 10:35:58 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_set_prevs(t_subshell *subshell)
{
	t_subshell	*tmp;

	tmp = subshell;
	while (tmp)
	{
		if (tmp->cmds)
			ft_set_prevs(tmp->cmds);
		if (tmp->next)
			tmp->next->prev = tmp;
		tmp = tmp->next;
	}
}
