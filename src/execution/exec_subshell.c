/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:04:14 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/07 00:53:19 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_get_right_subshell(t_subshell *subshell)
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
	// free_all(subshell, 0);
	return (0);
}

int	ft_exec_first_subshell(t_subshell *subshell)
{
	pid_t	pid;
	int		status;
	int		pipefd[2];

	status = 0;
	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		ft_get_right_subshell(subshell);
		exit(0);
	}
	else
	{
		close(pipefd[1]);
		subshell->pipe_read_end = pipefd[0];
		subshell->pid = pid;
	}
	g_exit = WEXITSTATUS(status);
	subshell->exit_status = g_exit;
	return (g_exit);
}

int	ft_exec_middle_subshell(t_subshell *subshell)
{
	pid_t	pid;
	int		status;
	int		pipefd[2];

	status = 0;
	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		dup2(subshell->prev->pipe_read_end, STDIN_FILENO);
		close(subshell->prev->pipe_read_end);
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		ft_get_right_subshell(subshell);
		exit(0);
	}
	else
	{
		close(subshell->prev->pipe_read_end);
		close(pipefd[1]);
		subshell->pipe_read_end = pipefd[0];
		subshell->pid = pid;
	}
	g_exit = WEXITSTATUS(status);
	subshell->exit_status = g_exit;
	return (g_exit);
}

int	ft_exec_last_subshell(t_subshell *subshell)
{
	pid_t	pid;
	int		status;
	int		pipefd[2];

	status = 0;
	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		dup2(subshell->prev->pipe_read_end, STDIN_FILENO);
		close(subshell->prev->pipe_read_end);
		ft_get_right_subshell(subshell);
		exit(0);
	}
	else
	{
		close(subshell->prev->pipe_read_end);
		subshell->pid = pid;
	}
	g_exit = WEXITSTATUS(status);
	subshell->exit_status = g_exit;
	return (g_exit);
}

void	ft_exec_subshell(t_subshell *subshell)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		if (subshell->link == PIPE && (!subshell->prev || subshell->prev->link != PIPE))
			ft_exec_first_subshell(subshell);
		else if (subshell->link == PIPE && subshell->prev && subshell->prev->link == PIPE)
			ft_exec_middle_subshell(subshell);
		else if (subshell->prev && subshell->prev->link == PIPE)
			ft_exec_last_subshell(subshell);
		else
			ft_get_right_subshell(subshell);
		exit(0);
	}
	else
	{
		subshell->pid = pid;
		subshell->exit_status = WEXITSTATUS(g_exit);
	}
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
