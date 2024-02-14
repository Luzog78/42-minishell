/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_check_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:33:58 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/14 03:34:09 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	bi_check_var(char *var)
{
	int	i;

	i = 1;
	if (!var)
		return (0);
	if ((var[0] < 'A' || var[0] > 'Z')
		&& (var[0] < 'a' || var[0] > 'z')
		&& var[0] != '_' && var[0] != '$')
		return (0);
	while (var[i])
	{
		if (var[i] == '=' || (var[i] == '+' && var[i + 1] == '='))
			return (1);
		if ((var[i] < 'A' || var[i] > 'Z') && (var[i] < 'a' || var[i] > 'z')
			&& (var[i] < '0' || var[i] > '9') && var[i] != '_' && var[i] != '$')
			return (0);
		i++;
	}
	return (1);
}
