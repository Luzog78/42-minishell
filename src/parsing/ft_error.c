/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 08:50:25 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/13 08:50:52 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_error(int err, char *str, t_subshell *subshell_to_free)
{
	(void)subshell_to_free;
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (err);
}
