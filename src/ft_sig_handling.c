/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sig_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 02:09:55 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/13 00:16:59 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	ft_sig_nothing(int sig)
{
	(void)sig;
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

void	ft_sig_init(t_bool handle)
{
	if (!handle)
	{
		signal(SIGINT, ft_sig_nothing);
		signal(SIGQUIT, ft_sig_nothing);
	}
	else
	{
		signal(SIGINT, ft_sig_handling);
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
