/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 02:28:54 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 02:29:11 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_sort_list(t_str_lst **lst)
{
	t_str_lst	*cursor;
	t_str_lst	*tmp;
	char		*tmp_str;

	cursor = *lst;
	while (cursor)
	{
		tmp = cursor->next;
		while (tmp)
		{
			if (ft_strcmp_ignore_case(cursor->value, tmp->value) > 0)
			{
				tmp_str = cursor->value;
				cursor->value = tmp->value;
				tmp->value = tmp_str;
			}
			tmp = tmp->next;
		}
		cursor = cursor->next;
	}
}
