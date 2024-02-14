/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_parenthesis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:02:10 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/13 11:15:15 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ft_skip_separator(char **cursor)
{
	(*cursor)++;
	ft_skip_whitespace(cursor);
	if (ft_starts_with(*cursor, "&&")
		|| ft_starts_with(*cursor, "||")
		|| ft_starts_with(*cursor, "|&"))
		*cursor += 2;
	else if (ft_starts_with(*cursor, "|"))
		(*cursor)++;
}

void	ft_skip_parenthesis(char **cursor)
{
	char	quote;
	int		parenthesis;

	quote = 0;
	parenthesis = 1;
	while (**cursor)
	{
		if (**cursor == '\'' || **cursor == '"')
		{
			if (!quote)
				quote = **cursor;
			else if (quote == **cursor)
				quote = 0;
		}
		else if (**cursor == '(' && !quote)
			parenthesis++;
		else if (**cursor == ')' && !quote)
			parenthesis--;
		if (parenthesis <= 0)
			break ;
		(*cursor)++;
	}
	ft_skip_separator(cursor);
}
