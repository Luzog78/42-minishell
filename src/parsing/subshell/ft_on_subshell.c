/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_on_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 01:29:34 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/14 02:00:34 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_bool	ft_on_subshell_open(t_subshell *subshell, t_parsing_object *po)
{
	if (po->parsing_state == 1 || subshell->type != UNDEFINED)
	{
		subshell->exit_status = ft_error(2,
				"syntax error: unexpected parenthesis '('", NULL);
		return (TRUE);
	}
	subshell->type = SUBSHELL;
	po->cursor++;
	while (!po->ret && *po->cursor && !ft_is_empty(po->cursor))
	{
		po->curr_cmd = ft_subshell_add(
				&subshell->cmds, UNDEFINED, subshell->env);
		po->ret = ft_parse_subshell(po->curr_cmd, &po->cursor);
		if (po->curr_cmd->exit_status)
		{
			subshell->exit_status = po->curr_cmd->exit_status;
			return (TRUE);
		}
	}
	po->parsing_state = 2;
	po->ret = FALSE;
	return (FALSE);
}

static t_bool	ft_on_subshell_close(t_subshell *subshell, t_parsing_object *po)
{
	po->cursor++;
	if (subshell->type == UNDEFINED)
	{
		subshell->exit_status = ft_error(2,
				"syntax error: unexpected parenthesis ')'", NULL);
		return (TRUE);
	}
	po->ret = TRUE;
	return (TRUE);
}

t_bool	ft_on_subshell(t_subshell *subshell, t_parsing_object *po)
{
	return ((ft_starts_with(po->cursor, "(")
			&& ft_on_subshell_open(subshell, po))
		|| (ft_starts_with(po->cursor, ")")
			&& ft_on_subshell_close(subshell, po)));
}
