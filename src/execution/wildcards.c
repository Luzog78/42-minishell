/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:31:08 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/17 00:53:53 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_bool	ft_wildcard_allow(char *file, char *str)
{
	t_wc_token	tk;

	tk = (t_wc_token){0};
	ft_wc_tokenize(&tk, str);
	if (!ft_wc_allow_start(&tk, file))
		return (FALSE);
	if (!ft_wc_allow_end(&tk, file))
		return (FALSE);
	if (!ft_wc_allow_middle(&tk, file))
		return (FALSE);
	return (TRUE);
}

t_bool	ft_is_wildcard(char *str)
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
