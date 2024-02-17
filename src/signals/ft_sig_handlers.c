/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sig_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 06:18:29 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 03:32:45 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "utils.h"

void	manage_cmds(t_subshell *cmds, int pipe[2])
{
	static t_subshell	*stored_cmds;
	static int			stored_pipe[2];

	if (cmds != NULL && pipe != NULL)
	{
		stored_cmds = cmds;
		stored_pipe[0] = pipe[0];
		stored_pipe[1] = pipe[1];
	}
	if (cmds == NULL)
	{
		ft_free_cmds(stored_cmds);
		close(stored_pipe[0]);
		close(stored_pipe[1]);
	}
}

void	ft_sig_nothing(int sig)
{
	(void)sig;
	manage_cmds(NULL, NULL);
}

void	ft_sig_stop(int sig)
{
	(void)sig;
	printf("\n");
	manage_cmds(NULL, NULL);
	exit(130);
}

void	ft_sig_handling(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \b\b \b", 6);
	}
}
