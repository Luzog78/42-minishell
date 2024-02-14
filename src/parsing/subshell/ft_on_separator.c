/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_on_separator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 01:56:41 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/14 02:01:05 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_bool	ft_on_and(t_subshell *subshell, t_parsing_object *po)
{
	subshell->link = AND;
	po->cursor += 2;
	return (TRUE);
}

static t_bool	ft_on_or(t_subshell *subshell, t_parsing_object *po)
{
	subshell->link = OR;
	po->cursor += 2;
	return (TRUE);
}

static t_bool	ft_on_pipe_and(t_subshell *subshell, t_parsing_object *po)
{
	subshell->link = PIPE_AND;
	po->cursor += 2;
	return (TRUE);
}

static t_bool	ft_on_pipe(t_subshell *subshell, t_parsing_object *po)
{
	subshell->link = PIPE;
	po->cursor++;
	return (TRUE);
}

t_bool	ft_on_separator(t_subshell *subshell, t_parsing_object *po)
{
	return ((ft_starts_with(po->cursor, "&&") && ft_on_and(subshell, po))
		|| (ft_starts_with(po->cursor, "||") && ft_on_or(subshell, po))
		|| (ft_starts_with(po->cursor, "|&") && ft_on_pipe_and(subshell, po))
		|| (ft_starts_with(po->cursor, "|") && ft_on_pipe(subshell, po)));
}
