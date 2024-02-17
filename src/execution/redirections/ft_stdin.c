/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:15:30 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/17 02:46:55 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtins.h"

int	ft_stdin(t_subshell *cmds, t_stdin_lst *stdin)
{
	int	fd;

	fd = 0;
	while (stdin)
	{
		if (fd != 0)
			close(fd);
		if (stdin->type == HEREDOC)
			fd = ft_heredoc(cmds, stdin, cmds->env);
		else if (stdin->type == INFILE)
			fd = ft_dup_infiles(stdin->value, cmds->env);
		stdin = stdin->next;
	}
	if (fd == -1)
	{
		g_exit = 1;
		return (g_exit);
	}
	dup2(fd, 0);
	close(fd);
	return (g_exit);
}
