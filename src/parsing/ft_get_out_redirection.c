/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_out_redirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:59:45 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/13 09:59:57 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_out_type	ft_get_out_redirection(char *str)
{
	int	i;

	i = 0;
	ft_skip_whitespace(&str);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			break ;
		i++;
	}
	if (str[i] != '>')
		return (NO_OUT);
	if (str[i + 1] != '>')
		return (REPLACE);
	return (APPEND);
}
