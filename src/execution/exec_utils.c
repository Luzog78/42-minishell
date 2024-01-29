/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:05:30 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/29 19:07:27 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	allow_next(t_subshell *cmds)
{
	if (cmds->link == PIPE || cmds->link == PIPE_AND)
		return (1);
	if (cmds->link == AND && cmds->exit_status == 0)
		return (1);
	if (cmds->link == OR && cmds->exit_status != 0)
		return (1);
	return (0);
}

size_t	ft_lstsize(t_str_lst *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

char	**ft_lststr_to_char_array(t_str_lst *lst)
{
	char	**array;
	int		i;

	i = 0;
	array = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!array)
		return (NULL);
	while (lst)
	{
		array[i] = ft_strdup(lst->value);
		i++;
		lst = lst->next;
	}
	array[i] = NULL;
	return (array);
}
