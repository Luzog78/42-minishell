/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 22:46:42 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/13 00:16:12 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_exec(t_subshell *subshell)
{
	ft_sig_init(FALSE);
	subshell->stdin_fd = dup(STDIN_FILENO);
	subshell->stdout_fd = dup(STDOUT_FILENO);
	if (subshell->cmds && subshell->cmds->type == COMMAND)
	{
		subshell->cmds->env = ft_env_cpy(subshell->env);
		ft_exec_cmd(subshell->cmds);
		subshell->env = ft_env_owrite(subshell->cmds->env, subshell->env);
	}
	else if (subshell->cmds && subshell->cmds->type == SUBSHELL)
	{
		subshell->cmds->env = ft_env_cpy(subshell->env);
		ft_exec_subshell(subshell->cmds);
	}
	while (waitpid(-1, NULL, WNOHANG) != -1)
		;
	dup2(subshell->stdin_fd, 0);
	dup2(subshell->stdout_fd, 1);
	close(subshell->stdin_fd);
	close(subshell->stdout_fd);
	ft_free_cmds(subshell->cmds);
	ft_sig_init(TRUE);
}
