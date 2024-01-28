/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:30:02 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/28 21:36:22 by bcarolle         ###   ########.fr       */
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

int	ft_execve_bin(char **argv, t_subshell *cmds)
{
	pid_t	pid;

	ft_get_path(argv);
	pid = fork();
	if (pid == -1)
	{
		perror("minishell");
		return (1);
	}
	if (!pid)
	{
		if (cmds->pipe[1] != 0)
		{
			dup2(cmds->pipe[1], 1);
			close(cmds->pipe[1]);
		}
		if (execve(argv[0], argv, cmds->env) == -1)
		{
			perror("minishell");
			exit (1);
		}
		// free_all();
		exit (0);
	}
	else if (cmds->next && cmds->next->next == NULL)
	{
		waitpid(pid, NULL, 0);
		close(cmds->pipe[1]);
		dup2(cmds->next->pipe[0], 0);
		close(cmds->next->pipe[0]);
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}
