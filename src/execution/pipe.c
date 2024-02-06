/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:56:52 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/06 18:03:30 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_pipe(t_subshell *cmds)
{
	int	pipefd[2];

	if (pipe(pipefd) < 0)
	{
		perror("pipe");
		return (1);
	}
	(void)cmds;
	// cmds->pipe[1] = pipefd[1];
	// cmds->next->pipe[0] = pipefd[0];
	return (0);
}
