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

/*int	ft_getlast_index(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
		i++;
	return (i);
}*/

char	**ft_str_lst_to_args(t_str_lst *lst, char **env)
{
	char		**array;
	/*char		**tmp_array;
	int			i;
	int			j;*/

	array = NULL;
	while (lst)
	{
		ft_args_append_str(&array, ft_strdup(lst->value), env);
		/*i = ft_getlast_index(array);
		j = 0;
		if (lst->value[0] == '$' && array && array[i])
		{
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
		}*/
		lst = lst->next;
	}
	return (array);
}
