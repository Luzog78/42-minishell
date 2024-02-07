/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sig_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 02:09:55 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/07 16:28:40 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	ft_kill_subshell(t_subshell *subshell, int sig)
{
	t_subshell	*tmp;

	if (!subshell)
		return ;
	if (subshell->pid)
		kill(subshell->pid, SIGINT);
	while (subshell)
	{
		tmp = subshell->cmds;
		while (tmp)
		{
			if (tmp->type == SUBSHELL)
				ft_kill_subshell(tmp, sig);
			else if (tmp->pid == COMMAND && tmp->pid)
				kill(tmp->pid, sig);
			tmp = tmp->next;
		}
		subshell = subshell->next;
	}
}

static void	ft_sig_handling(int sig)
{
	static int					state = 0;
	static unsigned long long	ptr = 0;
	static t_subshell			**master = NULL;

	(void)master;
	if (state < 2)
	{
		ptr |= (unsigned long long)(unsigned int)sig << (state * 32);
		state++;
		if (state == 2)
			master = (t_subshell **)ptr;
	}
	else if (sig == SIGQUIT)
	{
		ft_kill_subshell(*master, sig);
		g_exit = 131;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		if (!(*master)->cmds)
			rl_redisplay();
	}
	else if (sig == SIGINT)
	{
		ft_kill_subshell(*master, sig);
		g_exit = 130;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		if (!(*master)->cmds)
			rl_redisplay();
	}
}

void	ft_sig_init(t_subshell **master)
{
	unsigned long long	ptr;

	ptr = (unsigned long long)master;
	ft_sig_handling(ptr & 0xFFFFFFFF);
	ft_sig_handling((ptr >> 32) & 0xFFFFFFFF);
	signal(SIGINT, ft_sig_handling);
	signal(SIGQUIT, ft_sig_handling);
}
