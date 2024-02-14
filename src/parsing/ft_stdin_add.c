/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdin_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:00:53 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/13 10:01:05 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_stdin_lst	*ft_stdin_add(t_stdin_lst **stdin, char *value, t_stdin_type type)
{
	t_stdin_lst	*new_stdin;
	t_stdin_lst	*tmp;

	new_stdin = ft_calloc(1, sizeof(t_stdin_lst));
	if (!new_stdin)
		return (NULL);
	new_stdin->value = value;
	new_stdin->type = type;
	if (!*stdin)
	{
		*stdin = new_stdin;
		return (new_stdin);
	}
	tmp = *stdin;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_stdin;
	return (new_stdin);
}
