/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:31:08 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/17 02:26:08 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_bool	wc_is_wildcard(char *str)
{
	char	quote;

	quote = 0;
	while (*str)
	{
		if (*str == '*' && !quote)
			return (TRUE);
		if (*str == '\'' || *str == '"')
		{
			if (!quote)
				quote = *str;
			else if (quote == *str)
				quote = 0;
		}
		str++;
	}
	return (FALSE);
}
