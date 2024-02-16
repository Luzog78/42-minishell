/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_lst_pop_back.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 23:59:43 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 00:00:33 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_str_lst_pop_back(t_str_lst **lst)
{
	t_str_lst	*tmp;
	t_str_lst	*prev;
	char		*ret;

	if (!*lst)
		return (NULL);
	tmp = *lst;
	prev = NULL;
	while (tmp->next)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (prev)
		prev->next = NULL;
	else
		*lst = NULL;
	ret = tmp->value;
	free(tmp);
	return (ret);
}
