/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:04:14 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/17 02:40:46 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	ft_get_right_subshell(t_subshell *subshell)
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

static void	ft_exec_first_subshell(t_subshell *subshell)
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

static void	ft_exec_middle_subshell(t_subshell *subshell)
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
	close(subshell->prev->pipe_read_end);
	close(pipefd[1]);
	subshell->pipe_read_end = pipefd[0];
	subshell->pid = pid;
}

static int	ft_exec_last_subshell(t_subshell *subshell)
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

void	ft_exec_subshell(t_subshell *ssh)
{
	if (ssh->stdin)
		ft_stdin(ssh, ssh->stdin);
	if (ssh->outfiles)
		ft_dup_outfiles(ssh->outfiles, ssh->env);
	if (ssh->link == PIPE && (!ssh->prev || ssh->prev->link != PIPE))
		ft_exec_first_subshell(ssh);
	else if (ssh->link == PIPE && ssh->prev && ssh->prev->link == PIPE)
		ft_exec_middle_subshell(ssh);
	else if (ssh->prev && ssh->prev->link == PIPE)
		ft_exec_last_subshell(ssh);
	else
		ft_get_right_subshell(ssh);
	dup2(ft_get_parent(ssh)->stdin_fd, STDIN_FILENO);
	dup2(ft_get_parent(ssh)->stdout_fd, STDOUT_FILENO);
	if (ssh->next && ssh->next->type == COMMAND && ft_allow_next_cmd(ssh))
	{
		ssh->next->env = ft_env_cpy(ssh->env);
		ft_exec_cmd(ssh->next);
	}
	else if (ssh->next && ssh->next->type == SUBSHELL && ft_allow_next_cmd(ssh))
	{
		ssh->next->env = ft_env_cpy(ssh->env);
		ft_exec_subshell(ssh->next);
	}
}
