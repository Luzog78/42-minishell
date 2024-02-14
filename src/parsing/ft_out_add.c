/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_out_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:00:21 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/13 10:52:45 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_out	*ft_out_add(t_out **out, int from, char *to, t_out_type type)
{
	t_out	*new_out;
	t_out	*tmp;

	if (!to)
		return (NULL);
	if (!*to)
		free(to);
	if (!*to)
		return (NULL);
	new_out = ft_calloc(1, sizeof(t_out));
	if (!new_out)
		return (NULL);
	new_out->from = from;
	new_out->to = to;
	new_out->type = type;
	if (!*out)
	{
		*out = new_out;
		return (new_out);
	}
	tmp = *out;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_out;
	return (new_out);
}
