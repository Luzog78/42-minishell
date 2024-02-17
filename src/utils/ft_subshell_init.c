/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subshell_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:30:27 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 04:06:28 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_subshell_init(t_subshell *subshell, t_cmd_type type, char **env)
{
	subshell->type = type;
	subshell->env = NULL;
	subshell->pid = 0;
	if (type == SUBSHELL)
		subshell->env = ft_env_cpy(env);
	subshell->exit_status = 0;
	subshell->cmds = NULL;
	subshell->argv = NULL;
	subshell->stdin = NULL;
	subshell->outfiles = NULL;
	subshell->link = NONE;
	subshell->next = NULL;
	subshell->prev = NULL;
	subshell->parent = NULL;
	subshell->pipe_read_end = 0;
	subshell->stdin_fd = 0;
	subshell->stdout_fd = 1;
	subshell->pid = 0;
}
