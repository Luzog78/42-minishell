/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subshell_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 08:50:25 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/13 08:51:05 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_subshell	*ft_subshell_add(t_subshell **subshell, t_cmd_type type, char **env)
{
	t_subshell	*new_subshell;
	t_subshell	*tmp;

	new_subshell = ft_calloc(1, sizeof(t_subshell));
	if (!new_subshell)
		return (NULL);
	ft_subshell_init(new_subshell, type, env);
	if (!*subshell)
	{
		*subshell = new_subshell;
		return (new_subshell);
	}
	tmp = *subshell;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_subshell;
	return (new_subshell);
}
