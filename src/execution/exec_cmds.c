/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:57:48 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/06 17:31:49 by bcarolle         ###   ########.fr       */
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

int	ft_execve_pipe(t_subshell *cmds)
{
	pid_t	pid;
	int		status;
	int		end[2];

	status = 0;
	pipe(end);
	pid = fork();
	if (pid == -1)
	{
		perror("minishell");
		return (1);
	}
	if (!pid)
	{
		dup2(end[1], 1);
		close(end[0]);
		close(end[1]);
		get_right_cmds(cmds);
		exit(0);
	}
	else
	{
		dup2(end[0], 0);
		close(end[0]);
		close(end[1]);
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
	if (!cmds->exit_status && cmds->link == PIPE)
		cmds->exit_status = ft_execve_pipe(cmds);
	// else if (!cmds->exit_status && cmds->prev && cmds->prev->link == PIPE)
	// 	cmds->exit_status = ft_execve_last_pipe(cmds);
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
