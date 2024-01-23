/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:56:52 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/23 21:03:17 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_pipe(t_subshell *cmds)
{
	if (pipe(cmds->pipe) < 0)
	{
		perror("pipe");
		return (1);
	}
	return (0);
}
