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
	char		**array;
	char		**tmp_array;
	int			i;
	int			j;

	array = NULL;
	i = 0;
	while (lst)
	{
		j = 0;
		ft_args_append_str(&array, ft_strdup(lst->value), env);
		if (lst->value[0] == '$')
		{
			if (!array || !array[i])
			{
				lst = lst->next;
				continue ;
			}
			tmp_array = ft_split(array[i], ' ');
			if (strcmp(tmp_array[0], array[i]) == 0)
			{
				ft_free_char_array(tmp_array);
				lst = lst->next;
				continue ;
			}
			free(array[i]);
			array[i] = NULL;
			while (tmp_array && tmp_array[j])
			{
				ft_args_append_str(&array, ft_strdup(tmp_array[j]), env);
				free(tmp_array[j]);
				j++;
				if (tmp_array[j])
					i++;
			}
			free(tmp_array);
		}
		i++;
		lst = lst->next;
	}
	return (array);
}
