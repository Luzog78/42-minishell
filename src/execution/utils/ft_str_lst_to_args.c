/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_lst_to_args.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 02:27:28 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 02:36:38 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	**ft_str_lst_to_args(t_str_lst *lst, char **env)
{
	char	**array;

	array = NULL;
	while (lst)
	{
		ft_args_append_str(&array, ft_strdup(lst->value), env);
		lst = lst->next;
	}
	return (array);
}
