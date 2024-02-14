/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_parenthesis_and_quotes.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:01:44 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/13 10:52:08 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_bool	ft_check_parenthesis_and_quotes(char *str)
{
	int		i;
	char	quote;
	int		parenthesis;

	i = 0;
	quote = 0;
	parenthesis = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (!quote)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
		}
		else if (str[i] == '(' && !quote)
			parenthesis++;
		else if (str[i] == ')' && !quote)
			parenthesis--;
		if (parenthesis < 0)
			return (FALSE);
		i++;
	}
	return (!(quote || parenthesis));
}
