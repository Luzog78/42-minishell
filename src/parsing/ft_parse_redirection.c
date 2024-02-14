/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:01:22 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/13 10:45:56 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_parse_redirection(t_subshell *subshell, char **str)
{
	int		fd;
	t_out	*ret;

	ft_skip_whitespace(str);
	fd = 1;
	if (**str >= '0' && **str <= '9')
		fd = ft_get_next_int(str);
	(*str)++;
	if (**str != '>')
		ret = ft_out_add(&subshell->outfiles, fd,
				ft_get_next_word(str), REPLACE);
	else
	{
		(*str)++;
		ret = ft_out_add(&subshell->outfiles, fd,
				ft_get_next_word(str), APPEND);
	}
	if (!ret)
		subshell->exit_status = ft_error(2,
				"syntax error: missing redirection statement", NULL);
}
