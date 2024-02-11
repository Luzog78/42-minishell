/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:04:14 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/11 22:43:13 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_get_right_subshell(t_subshell *subshell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (ft_perror());
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
		ft_free_cmds(ft_get_parent(subshell));
		exit(g_exit);
	}
	else
	{
		waitpid(pid, &g_exit, 0);
		g_exit = WEXITSTATUS(g_exit);
	}
}

void	ft_exec_first_subshell(t_subshell *subshell)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (ft_perror());
	pid = fork();
	if (pid == -1)
		return (ft_perror());
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		ft_get_right_subshell(subshell);
		ft_free_cmds(ft_get_parent(subshell));
		exit(g_exit);
	}
	else
	{
		close(pipefd[1]);
		subshell->pipe_read_end = pipefd[0];
		subshell->pid = pid;
	}
}

void	ft_exec_middle_subshell(t_subshell *subshell)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (ft_perror());
	pid = fork();
	if (pid == -1)
		return (ft_perror());
	if (pid == 0)
	{
		dup2(subshell->prev->pipe_read_end, STDIN_FILENO);
		close(subshell->prev->pipe_read_end);
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		ft_get_right_subshell(subshell);
		ft_free_cmds(ft_get_parent(subshell));
		exit(g_exit);
	}
	else
	{
		close(subshell->prev->pipe_read_end);
		close(pipefd[1]);
		subshell->pipe_read_end = pipefd[0];
		subshell->pid = pid;
	}
}

int	ft_exec_last_subshell(t_subshell *subshell)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		ft_perror();
		return (g_exit);
	}
	if (pid == 0)
	{
		dup2(subshell->prev->pipe_read_end, STDIN_FILENO);
		close(subshell->prev->pipe_read_end);
		ft_get_right_subshell(subshell);
		ft_free_cmds(ft_get_parent(subshell));
		exit(g_exit);
	}
	subshell->pid = pid;
	waitpid(pid, &status, 0);
	close(subshell->prev->pipe_read_end);
	if (!g_exit)
		g_exit = WEXITSTATUS(status);
	subshell->exit_status = g_exit;
	return (g_exit);
}

void	ft_exec_subshell(t_subshell *subshell)
{
	if (subshell->link == PIPE
		&& (!subshell->prev || subshell->prev->link != PIPE))
		ft_exec_first_subshell(subshell);
	else if (subshell->link == PIPE
		&& subshell->prev && subshell->prev->link == PIPE)
		ft_exec_middle_subshell(subshell);
	else if (subshell->prev && subshell->prev->link == PIPE)
		ft_exec_last_subshell(subshell);
	else
		ft_get_right_subshell(subshell);
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
	g_exit = subshell->exit_status;
}
