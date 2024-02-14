/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:59:10 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/13 09:59:22 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_get_next_int(char **str)
{
	int		nb;
	char	*tmp;

	ft_skip_whitespace(str);
	tmp = *str;
	nb = 0;
	while (*tmp && *tmp >= '0' && *tmp <= '9')
	{
		nb = nb * 10 + *tmp - '0';
		tmp++;
	}
	*str = tmp;
	return (nb);
}
