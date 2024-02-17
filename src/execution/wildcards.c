/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:31:08 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/17 01:45:09 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_bool	ft_wildcard_allow(char *file, char *str)
{
	t_wc_token	tk;
	t_bool		ret;

	tk = (t_wc_token){0};
	ft_wc_tokenize(&tk, str);
	ret = TRUE;
	if (!ft_wc_allow_start(&tk, file) || !ft_wc_allow_end(&tk, file) || !ft_wc_allow_middle(&tk, file))
		ret = FALSE;
	free(str);
	free(tk.start);
	free(tk.end);
	ft_free_str_lst(tk.tks);
	return (ret);
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
