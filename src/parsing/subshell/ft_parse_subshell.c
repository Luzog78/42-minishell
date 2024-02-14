/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_subshell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:36:33 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/14 02:00:55 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_bool	ft_on_argv(t_subshell *subshell, t_parsing_object *po)
{
	if (subshell->type == SUBSHELL)
	{
		subshell->exit_status = ft_error(2,
				"syntax error: subshell and command not separated", NULL);
		return (TRUE);
	}
	subshell->type = COMMAND;
	if (po->parsing_state == 0)
		po->parsing_state = 1;
	if (po->parsing_state == 2)
		subshell->exit_status = ft_error(2,
				"syntax error: missing a separator", NULL);
	po->tmp = ft_get_next_word(&po->cursor);
	ft_str_lst_add(&subshell->argv, po->tmp);
	return (FALSE);
}

void	ft_init_po(t_subshell *subshell, char **str, t_parsing_object *po)
{
	po->curr_cmd = subshell->cmds;
	po->cursor = *str;
	po->ret = FALSE;
	po->parsing_state = 0;
	if (!*po->cursor || ft_is_empty(po->cursor))
		subshell->exit_status = ft_error(2,
				"syntax error: missing command", NULL);
}

t_bool	ft_on_char(t_subshell *subshell, t_parsing_object *po)
{
	if (ft_starts_with(po->cursor, "(") || ft_starts_with(po->cursor, ")"))
		return (ft_on_subshell(subshell, po));
	if (ft_starts_with(po->cursor, "<<")
		|| ft_starts_with(po->cursor, "<")
		|| ft_get_out_redirection(po->cursor) != NO_OUT)
		return (ft_on_redir(subshell, po));
	if (ft_starts_with(po->cursor, "&&")
		|| ft_starts_with(po->cursor, "||")
		|| ft_starts_with(po->cursor, "|&")
		|| ft_starts_with(po->cursor, "|"))
		return (ft_on_separator(subshell, po));
	if (ft_starts_with(po->cursor, "#"))
	{
		while (*po->cursor)
			po->cursor++;
		return (TRUE);
	}
	return (ft_on_argv(subshell, po));
}

t_bool	ft_parse_subshell(t_subshell *subshell, char **str)
{
	t_parsing_object	po;

	ft_init_po(subshell, str, &po);
	while (*po.cursor && !ft_is_empty(po.cursor))
	{
		ft_skip_whitespace(&po.cursor);
		if (ft_on_char(subshell, &po))
			break ;
	}
	*str = po.cursor;
	if (subshell->type == UNDEFINED)
		subshell->exit_status = ft_error(2,
				"syntax error: missing command", NULL);
	return (po.ret);
}
