/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_lst_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 08:54:55 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/13 09:55:17 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_str_lst	*ft_str_lst_add(t_str_lst **lst, char *str)
{
	t_str_lst	*new_argv;
	t_str_lst	*tmp;

	new_argv = ft_calloc(1, sizeof(t_str_lst));
	if (!new_argv)
		return (NULL);
	new_argv->value = str;
	new_argv->next = NULL;
	if (!*lst)
	{
		*lst = new_argv;
		return (new_argv);
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_argv;
	return (new_argv);
}
