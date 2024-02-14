/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_on_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 01:56:16 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/14 02:01:25 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_bool	ft_on_heredoc(t_subshell *subshell, t_parsing_object *po)
{
	po->cursor += 2;
	po->tmp = ft_get_next_word(&po->cursor);
	if (!*po->tmp)
		subshell->exit_status = ft_error(2,
				"syntax error: missing heredoc delimiter", NULL);
	ft_stdin_add(&subshell->stdin, po->tmp, HEREDOC);
	if (po->parsing_state == 1)
		po->parsing_state = 2;
	return (FALSE);
}

static t_bool	ft_on_infile(t_subshell *subshell, t_parsing_object *po)
{
	po->cursor++;
	po->tmp = ft_get_next_word(&po->cursor);
	if (!*po->tmp)
		subshell->exit_status = ft_error(2,
				"syntax error: missing input file", NULL);
	ft_stdin_add(&subshell->stdin, po->tmp, INFILE);
	if (po->parsing_state == 1)
		po->parsing_state = 2;
	return (FALSE);
}

static t_bool	ft_on_outfile(t_subshell *subshell, t_parsing_object *po)
{
	ft_parse_redirection(subshell, &po->cursor);
	if (po->parsing_state == 1)
		po->parsing_state = 2;
	return (FALSE);
}

t_bool	ft_on_redir(t_subshell *subshell, t_parsing_object *po)
{
	return ((ft_starts_with(po->cursor, "<<") && ft_on_heredoc(subshell, po))
		|| (ft_starts_with(po->cursor, "<") && ft_on_infile(subshell, po))
		|| (ft_get_out_redirection(po->cursor) != NO_OUT
			&& ft_on_outfile(subshell, po)));
}
