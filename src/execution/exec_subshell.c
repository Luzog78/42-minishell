/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:04:14 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/04 03:15:39 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_exec_subshell(t_subshell *subshell)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (!subshell)
		return ;
	if (subshell->link == PIPE)
		ft_pipe(subshell);
	pid = fork();
	if (pid == 0)
	{
		if (subshell->pipe[1] != 0)
		{
			dup2(subshell->pipe[1], 1);
			close(subshell->pipe[1]);
		}
		if (subshell->cmds && subshell->cmds->type == COMMAND)
		{
			subshell->cmds->env = ft_env_cpy(subshell->env);
			ft_exec_cmd(subshell->cmds);
		}
		else if (subshell->cmds && subshell->cmds->type == SUBSHELL)
		{
			subshell->cmds->env = ft_env_cpy(subshell->env);
			ft_exec_subshell(subshell->cmds);
		}
		free_all(subshell, 0);
		exit(0);
	}
	else if (subshell->next && subshell->next->pipe[0] != 0)
	{
		close(subshell->pipe[1]);
		dup2(subshell->next->pipe[0], 0);
		close(subshell->next->pipe[0]);
	}
	else
	{
		subshell->pid = pid;
		waitpid(-1, &status, 0);
	}
	g_exit = WEXITSTATUS(status);
	subshell->exit_status = g_exit;
	if (subshell->next && subshell->next->type == COMMAND
		&& allow_next(subshell))
	{
		subshell->next->env = ft_env_cpy(subshell->env);
		ft_exec_cmd(subshell->next);
	}
	else if (subshell->next && subshell->next->type == SUBSHELL
		&& allow_next(subshell))
	{
		subshell->next->env = ft_env_cpy(subshell->env);
		ft_exec_subshell(subshell->next);
	}
}
