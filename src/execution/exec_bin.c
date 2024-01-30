/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:30:02 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/30 03:21:24 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_get_path(char **argv)
{
	char	**path;
	char	*tmp;
	int		i;

	i = 0;
	path = ft_split(getenv("PATH"), ':');
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

int	ft_execve_bin_piped(char **argv, t_subshell *cmds)
{
	ft_get_path(argv);
	if (execve(argv[0], argv, cmds->env) == -1)
		perror("minishell");
	ft_free_char_array(argv);
	return (0);
}

int	ft_execve_bin(char **argv, t_subshell *cmds)
{
	pid_t	pid;

	ft_get_path(argv);
	pid = fork();
	if (pid == -1)
	{
		perror("minishell");
		return (0);
	}
	if (!pid)
	{
		if (cmds->pipe[0] != 0)
		{
			dup2(cmds->pipe[0], 0);
			close(cmds->pipe[0]);
		}
		exit(execve(argv[0], argv, cmds->env));
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}
