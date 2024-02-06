/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:57:48 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/07 00:34:32 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	get_right_cmds(t_subshell *cmds)
{
	char	**argv;
	int		exit_status;

	argv = ft_lststr_to_char_array(cmds->argv);
	if (ft_strcmp(argv[0], "echo") == 0)
		exit_status = ft_echo(argv, cmds->env);
	else if (ft_strcmp(argv[0], "cd") == 0)
		exit_status = ft_cd(argv, cmds);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		exit_status = ft_pwd(cmds->env);
	else if (ft_strcmp(argv[0], "export") == 0)
		exit_status = ft_export(argv + 1, cmds);
	else if (ft_strcmp(argv[0], "unset") == 0)
		exit_status = ft_unset(argv, cmds);
	else if (ft_strcmp(argv[0], "env") == 0)
		exit_status = ft_env(argv, cmds->env);
	else if (ft_strcmp(argv[0], "exit") == 0)
		exit_status = ft_exit(argv);
	else
		exit_status = ft_execve_bin(argv, cmds);
	g_exit = exit_status;
	ft_free_char_array(argv);
	return (exit_status);
}

int	ft_execve_first_pipe(t_subshell *cmds)
{
	int		pipefd[2];
	pid_t	pid;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		get_right_cmds(cmds);
		exit(1);
	}
	else
	{
		close(pipefd[1]);
		cmds->pipe_read_end = pipefd[0];
	}
	return (0);
}

int	ft_execve_pipe(t_subshell *cmds)
{
	pid_t	pid;
	int		status;
	int		pipefd[2];

	status = 0;
	pipe(pipefd);
	pid = fork();
	if (pid == -1)
	{
		perror("minishell");
		return (1);
	}
	if (!pid)
	{
		dup2(cmds->prev->pipe_read_end, STDIN_FILENO);
		close(cmds->prev->pipe_read_end);
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		get_right_cmds(cmds);
		exit(1);
	}
	else
	{
		close(cmds->prev->pipe_read_end);
		close(pipefd[1]);
		cmds->pipe_read_end = pipefd[0];
	}
	g_exit = WEXITSTATUS(status);
	cmds->exit_status = g_exit;
	return (g_exit);
}

int	ft_execve_last_pipe(t_subshell *cmds)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("minishell");
		return (1);
	}
	if (!pid)
	{
		dup2(cmds->prev->pipe_read_end, STDIN_FILENO);
		close(cmds->prev->pipe_read_end);
		get_right_cmds(cmds);
		exit(0);
	}
	else
	{
		close(cmds->prev->pipe_read_end);
	}
	g_exit = WEXITSTATUS(status);
	cmds->exit_status = g_exit;
	return (g_exit);
}



void	ft_exec_cmd(t_subshell *cmds)
{
	if (!cmds->exit_status && cmds->stdin)
		cmds->exit_status = ft_stdin(cmds->stdin, cmds->env);
	if (!cmds->exit_status && cmds->outfiles)
		cmds->exit_status = ft_dup_outfiles(cmds->outfiles);
	if (!cmds->exit_status && cmds->link == PIPE && (!cmds->prev || cmds->prev->link != PIPE))
		cmds->exit_status = ft_execve_first_pipe(cmds);
	else if (!cmds->exit_status && cmds->link == PIPE && cmds->prev && cmds->prev->link == PIPE)
		cmds->exit_status = ft_execve_pipe(cmds);
	else if (!cmds->exit_status && cmds->prev && cmds->prev->link == PIPE)
		cmds->exit_status = ft_execve_last_pipe(cmds);
	else if (!cmds->exit_status && cmds->argv)
		cmds->exit_status = get_right_cmds(cmds);
	if (cmds->next == NULL)
		return ;
	cmds->next->env = ft_env_cpy(cmds->env);
	if (cmds->next->type == COMMAND && allow_next(cmds))
		ft_exec_cmd(cmds->next);
	if (cmds->next->type == SUBSHELL && allow_next(cmds))
		ft_exec_subshell(cmds->next);
}
