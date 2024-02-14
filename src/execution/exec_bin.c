/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:30:02 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/14 04:17:25 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	ft_get_path(char **argv, char **env)
{
	char	**path;
	char	*tmp;
	int		i;

	i = 0;
	path = ft_split(ft_getenv("PATH", env), ':');
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i] = ft_strjoin(tmp, argv[0]);
		free(tmp);
		if (access(path[i], F_OK) == 0)
		{
			free(argv[0]);
			argv[0] = ft_strdup(path[i]);
			ft_free_char_array(path);
			return ;
		}
		i++;
	}
	ft_free_char_array(path);
}

static void	ft_child_execve_bin(char **argv, t_subshell *cmds)
{
	if (access(argv[0], F_OK) == -1)
	{
		perror("minishell:");
		ft_free_char_array(argv);
		ft_free_cmds(ft_get_parent(cmds));
		exit(127);
	}
	if (access(argv[0], X_OK) == -1)
	{
		perror("minishell");
		ft_free_char_array(argv);
		ft_free_cmds(ft_get_parent(cmds));
		exit(126);
	}
	if (ft_get_parent(cmds)->stdin_fd != STDIN_FILENO)
		close(ft_get_parent(cmds)->stdin_fd);
	if (ft_get_parent(cmds)->stdout_fd != STDOUT_FILENO)
		close(ft_get_parent(cmds)->stdout_fd);
	execve(argv[0], argv, cmds->env);
	perror("minishell");
	ft_free_char_array(argv);
	ft_free_cmds(ft_get_parent(cmds));
	exit(errno);
}

int	ft_execve_bin(char **argv, t_subshell *cmds)
{
	pid_t	pid;
	int		status;

	status = 0;
	ft_get_path(argv, cmds->env);
	pid = fork();
	if (pid == -1)
	{
		perror("minishell");
		return (0);
	}
	if (!pid)
		ft_child_execve_bin(argv, cmds);
	else
	{
		waitpid(pid, &status, 0);
		cmds->pid = pid;
		ft_sig_exit(status);
		cmds->exit_status = g_exit;
	}
	return (g_exit);
}
