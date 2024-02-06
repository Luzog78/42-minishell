/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:04:14 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/06 18:55:43 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// void	ft_exec_first_subshell(t_subshell *subshell)
// {

// }

// void	ft_execve_last_subshell(t_subshell *subshell)
// {

// }

void	ft_exec_subshell(t_subshell *subshell)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
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
