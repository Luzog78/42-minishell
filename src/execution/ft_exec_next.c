/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_next.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 12:12:59 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/17 12:13:25 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_exec_next(t_subshell *subshell)
{
	while (subshell->next)
	{
		if (ft_allow_next_cmd(subshell))
		{
			subshell->next->env = ft_env_cpy(subshell->env);
			if (subshell->next->type == COMMAND)
				ft_exec_cmd(subshell->next);
			else if (subshell->next->type == SUBSHELL)
				ft_exec_subshell(subshell->next);
			break ;
		}
		subshell = subshell->next;
	}
}
