/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:57:48 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/17 09:19:00 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	get_right_cmds(t_subshell *cmds, char **argv,
	int exit_status, int i)
{
	static int	(*arr[8])(char **, t_subshell *) = {ft_execve_bin, ft_echo,
		ft_cd, ft_pwd, ft_export, ft_unset, ft_env, ft_exit};
	static char	*c[7] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};

	if (!cmds->exit_status && cmds->stdin)
		cmds->exit_status = ft_stdin(cmds, cmds->stdin);
	if (!cmds->exit_status && cmds->outfiles)
		cmds->exit_status = ft_dup_outfiles(cmds->outfiles, cmds->env);
	if (cmds->exit_status)
		return (cmds->exit_status);
	argv = ft_str_lst_to_args(cmds->argv, cmds->env);
	if (!argv)
		exit_status = g_exit;
	while (argv && ++i <= 8)
	{
		if (i == 8)
			exit_status = (*arr[0])(argv, cmds);
		else if (!ft_strcmp(argv[0], c[i - 1]))
			exit_status = (*arr[i])(argv, cmds);
		if (!ft_strcmp(argv[0], c[i - 1]))
			break ;
	}
	g_exit = exit_status;
	ft_free_char_array(argv);
	return (exit_status);
}

static void	ft_execve_first_pipe(t_subshell *cmds)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	status = 0;
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
		if (cmds->outfiles)
			ft_dup_outfiles(cmds->outfiles, cmds->env);
		if (!cmds->exit_status)
			status = get_right_cmds(cmds, NULL, 0, 0);
		ft_free_cmds(ft_get_parent(cmds));
		exit(status);
	}
	close(pipefd[1]);
	cmds->pipe_read_end = pipefd[0];
}

static void	ft_execve_pipe(t_subshell *cmds)
{
	pid_t	pid;
	int		status;
	int		pipefd[2];

	status = 0;
	if (pipe(pipefd) == -1)
		return (ft_perror());
	pid = fork();
	if (pid == -1)
		return (ft_perror());
	if (!pid)
	{
		dup2(cmds->prev->pipe_read_end, STDIN_FILENO);
		close(cmds->prev->pipe_read_end);
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		status = get_right_cmds(cmds, NULL, 0, 0);
		ft_free_cmds(ft_get_parent(cmds));
		exit(status);
	}
	close(cmds->prev->pipe_read_end);
	close(pipefd[1]);
	cmds->pipe_read_end = pipefd[0];
}

static int	ft_execve_last_pipe(t_subshell *cmds)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		return (ft_perror_ret());
	if (!pid)
	{
		if (!cmds->stdin)
			dup2(cmds->prev->pipe_read_end, STDIN_FILENO);
		close(cmds->prev->pipe_read_end);
		status = get_right_cmds(cmds, NULL, 0, 0);
		ft_free_cmds(ft_get_parent(cmds));
		exit(status);
	}
	waitpid(pid, &status, 0);
	g_exit = WEXITSTATUS(status);
	close(cmds->prev->pipe_read_end);
	if (!g_exit)
		ft_sig_exit(status);
	cmds->exit_status = g_exit;
	return (g_exit);
}

void	ft_exec_cmd(t_subshell *cmds)
{
	if (cmds->link == PIPE
		&& (!cmds->prev || cmds->prev->link != PIPE))
		ft_execve_first_pipe(cmds);
	else if (!cmds->exit_status && cmds->link == PIPE
		&& cmds->prev && cmds->prev->link == PIPE)
		ft_execve_pipe(cmds);
	else if (!cmds->exit_status && cmds->prev && cmds->prev->link == PIPE)
		cmds->exit_status = ft_execve_last_pipe(cmds);
	else if (!cmds->exit_status && cmds->argv)
		cmds->exit_status = get_right_cmds(cmds, NULL, 0, 0);
	if (cmds->next == NULL)
		return ;
	cmds->next->env = ft_env_cpy(cmds->env);
	if (cmds->next->type == COMMAND && ft_allow_next_cmd(cmds))
		ft_exec_cmd(cmds->next);
	if (cmds->next->type == SUBSHELL && ft_allow_next_cmd(cmds))
		ft_exec_subshell(cmds->next);
}
