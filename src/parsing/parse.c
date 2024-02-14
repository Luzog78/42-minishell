/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 03:07:38 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/13 10:45:18 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_parse(t_subshell *subshell, char *str)
{
	t_bool		ret;
	char		*cursor;
	t_subshell	*curr_cmd;

	subshell->exit_status = 0;
	ret = FALSE;
	cursor = str;
	while (!ret && *cursor && !ft_is_empty(cursor))
	{
		curr_cmd = ft_subshell_add(&subshell->cmds, UNDEFINED, subshell->env);
		ret = ft_parse_subshell(curr_cmd, &cursor);
		if (curr_cmd->exit_status)
		{
			subshell->exit_status = curr_cmd->exit_status;
			break ;
		}
	}
	ft_set_parents(subshell);
	ft_set_prevs(subshell);
	curr_cmd = subshell->cmds;
	while (curr_cmd && curr_cmd->next)
		curr_cmd = curr_cmd->next;
	if (curr_cmd && curr_cmd->link != NONE)
		subshell->exit_status = ft_error(2,
				"syntax error: missing command", NULL);
}
