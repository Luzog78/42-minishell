/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_out_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:00:21 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 10:39:12 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ft_set_new_out(t_out *new_out, int from, char *to, t_out_type type)
{
	new_out->from = from;
	new_out->to = to;
	new_out->type = type;
}

t_out	*ft_out_add(t_out **out, int from, char *to, t_out_type type)
{
	t_out	*new_out;
	t_out	*tmp;

	if (!to)
		return (NULL);
	if (!*to)
	{
		free(to);
		return (NULL);
	}
	new_out = ft_calloc(1, sizeof(t_out));
	if (!new_out)
		return (NULL);
	ft_set_new_out(new_out, from, to, type);
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
