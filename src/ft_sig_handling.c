/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sig_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 02:09:55 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/14 03:32:14 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

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

static void	ft_sig_nothing(int sig)
{
	(void)sig;
	manage_cmds(NULL, NULL);
}

static void	ft_sig_stop(int sig)
{
	(void)sig;
	printf("\n");
	manage_cmds(NULL, NULL);
	exit(130);
}

static void	ft_sig_handling(int sig)
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
	// ft_sig_init(TRUE);
}
