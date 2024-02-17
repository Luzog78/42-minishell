/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve_bin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:30:02 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/17 09:14:21 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_bool	ft_get_path(char **argv, char **env)
{
	char	**path;
	char	*tmp;
	int		i;

	i = 0;
	if (argv[0][0] == '.' || argv[0][0] == '/' || argv[0][0] == '~')
		return (TRUE);
	path = ft_split(ft_getenv("PATH", env), ':');
	while (path && path[i])
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
			return (TRUE);
		}
		i++;
	}
	ft_free_char_array(path);
	return (FALSE);
}

static void	ft_bin_error_handling(char **argv, t_subshell *cmds)
{
	int	status;

	status = 0;
	if (access(argv[0], F_OK) == -1)
		status = 127;
	else if (access(argv[0], X_OK) == -1)
		status = 126;
	if (access(argv[0], X_OK) == -1 && (argv[0][0] != '/' && argv[0][0] != '.'))
		status = 127;
	if (opendir(argv[0]))
		status = 127;
	if (opendir(argv[0]) && (argv[0][0] == '/' || argv[0][0] == '.'))
		status = 126;
	ft_free_char_array(argv);
	ft_free_cmds(ft_get_parent(cmds));
	exit(status);
}

static void	ft_child_execve_bin(char **argv, t_subshell *cmds)
{
	if (ft_get_parent(cmds)->stdin_fd != STDIN_FILENO)
		close(ft_get_parent(cmds)->stdin_fd);
	if (ft_get_parent(cmds)->stdout_fd != STDOUT_FILENO)
		close(ft_get_parent(cmds)->stdout_fd);
	execve(argv[0], argv, cmds->env);
	perror("minishell");
	ft_bin_error_handling(argv, cmds);
}

int	ft_execve_bin(char **argv, t_subshell *cmds)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (!ft_get_path(argv, cmds->env))
	{
		ft_putstr_fd("minishell: command not found\n", STDERR_FILENO);
		g_exit = 127;
		return (g_exit);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell");
		return (0);
	}
	if (!pid)
		ft_child_execve_bin(argv, cmds);
	waitpid(pid, &status, 0);
	cmds->pid = pid;
	ft_sig_exit(status);
	cmds->exit_status = g_exit;
	return (g_exit);
}
