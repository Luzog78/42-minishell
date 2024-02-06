/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 22:46:42 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/06 18:57:28 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_exec(t_subshell *subshell)
{
	int	old_stdin;
	int	old_stdout;

	old_stdin = dup(0);
	old_stdout = dup(1);
	if (subshell->cmds && subshell->cmds->type == COMMAND)
	{
		subshell->cmds->env = ft_env_cpy(subshell->env);
		ft_exec_cmd(subshell->cmds);
		subshell->env = ft_env_owrite(subshell->cmds->env, subshell->env);
		while (waitpid(-1, NULL, WNOHANG) != -1)
			;
	}
	else if (subshell->cmds && subshell->cmds->type == SUBSHELL)
	{
		subshell->cmds->env = ft_env_cpy(subshell->env);
		ft_exec_subshell(subshell->cmds);
	}
	dup2(old_stdin, 0);
	dup2(old_stdout, 1);
	close(old_stdin);
	close(old_stdout);
	free_all(subshell, 0);
}
