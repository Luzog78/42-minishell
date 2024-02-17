/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_lst_add_back.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 23:54:27 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 00:17:45 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_str_lst_add_back(t_str_lst **lst, char *str)
{
	t_str_lst	*tmp;
	t_str_lst	*new_lst;

	new_lst = ft_calloc(1, sizeof(t_str_lst));
	if (!new_lst)
		return ;
	new_lst->value = str;
	if (!*lst)
	{
		*lst = new_lst;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_lst;
}
