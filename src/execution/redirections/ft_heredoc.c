/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 06:38:30 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/16 15:19:29 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtins.h"

static void	ft_here_child(t_heredoc hd)
{
	char	*line;

	ft_sig_init(2, hd.cmds, hd.pipefd);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, hd.stdin->value) || g_exit)
		{
			free(line);
			break ;
		}
		if (hd.is_formattable)
			line = ft_get_bash_string(line, hd.env, FALSE);
		if (line)
			ft_putstr_fd(line, hd.pipefd[1]);
		ft_putstr_fd("\n", hd.pipefd[1]);
		free(line);
	}
	close(hd.pipefd[0]);
	close(hd.pipefd[1]);
	ft_free_cmds(ft_get_parent(hd.cmds));
	exit(0);
}

int	ft_heredoc(t_subshell *cmds, t_stdin_lst *stdin, char **env)
{
	t_bool	is_formattable;
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
	{
		perror("minishell");
		return (-1);
	}
	stdin->value = ft_get_right_limiter(stdin->value, &is_formattable);
	pid = fork();
	if (!pid)
		ft_here_child((t_heredoc){cmds, stdin, env, pipefd, is_formattable});
	waitpid(-1, &status, 0);
	ft_sig_exit(status);
	close(pipefd[1]);
	return (pipefd[0]);
}
