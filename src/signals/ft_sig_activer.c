/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sig_activer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 02:09:55 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 03:33:05 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "utils.h"

/**
 * @brief
 *
 * @param	mode	> 0: no handling,
 * 					> 1: classic handling,
 * 					> 2: exit handling,
 */
void	ft_sig_init(int mode, t_subshell *cmds, int pipe[2])
{
	if (mode == 0)
	{
		manage_cmds(ft_get_parent(cmds), pipe);
		signal(SIGINT, ft_sig_nothing);
		signal(SIGQUIT, ft_sig_nothing);
		signal(SIGPIPE, ft_sig_nothing);
	}
	else if (mode == 1)
	{
		signal(SIGINT, ft_sig_handling);
		signal(SIGQUIT, ft_sig_handling);
	}
	else if (mode == 2)
	{
		manage_cmds(ft_get_parent(cmds), pipe);
		signal(SIGINT, ft_sig_stop);
		signal(SIGQUIT, ft_sig_handling);
	}
}

void	ft_sig_exit(int status)
{
	if (!WIFEXITED(status) && WTERMSIG(status) == SIGINT)
	{
		printf("\n");
		g_exit = 130;
	}
	else if (!WIFEXITED(status) && WTERMSIG(status) == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
		g_exit = 131;
	}
	else
		g_exit = WEXITSTATUS(status);
}
