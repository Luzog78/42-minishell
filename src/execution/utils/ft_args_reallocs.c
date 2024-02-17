/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_reallocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 02:34:25 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 02:34:38 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_args_reallocs(char ***args, t_str_lst **lst)
{
	t_str_lst	*cursor;
	t_str_lst	*tmp;

	cursor = *lst;
	while (cursor)
	{
		ft_args_realloc(args, cursor->value);
		free(cursor->value);
		tmp = cursor->next;
		free(cursor);
		cursor = tmp;
	}
	*lst = NULL;
}
