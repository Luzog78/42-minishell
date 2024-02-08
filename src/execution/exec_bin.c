/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:30:02 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/08 02:21:17 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_get_path(char **argv, char **env)
{
	char	**path;
	char	*tmp;
	char	*translated;
	int		i;

	translated = ft_get_bash_string(argv[0], env);
	free(argv[0]);
	argv[0] = translated;
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
	{
		if (access(argv[0], X_OK) == -1)
		{
			perror("minishell");
			ft_free_char_array(argv);
			ft_free_subshell(ft_get_parent(cmds));
			exit(127);
		}
		execve(argv[0], argv, cmds->env);
		perror("minishell");
		ft_free_char_array(argv);
		ft_free_subshell(ft_get_parent(cmds));
		exit(errno);
	}
	else
	{
		waitpid(pid, &status, 0);
		cmds->pid = pid;
		if (!g_exit)
			g_exit = WEXITSTATUS(status);
		cmds->exit_status = g_exit;
	}
	return (g_exit);
}
