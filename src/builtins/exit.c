/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:00:04 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/25 12:23:43 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_exit(void)
{
	//EXIT LE SUBSHELL LE PLUS PROCHE AUSSI HEIN
	//free all
	printf("exit\n");
	exit(0);
	return (0);
}
