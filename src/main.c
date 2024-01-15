/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 01:24:46 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/15 01:32:51 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	ft_subshell_init(t_subshell *subshell, t_cmd_type type, char **env)
{
	subshell->type = type;
	subshell->env = NULL;
	if (type == SUBSHELL)
		subshell->env = ft_env_cpy(env);
	subshell->exit_status = 0;
	subshell->cmds = NULL;
	subshell->argv = NULL;
	subshell->infile = NULL;
	subshell->outfiles = NULL;
	subshell->heredoc = NULL;
	subshell->link = NONE;
	subshell->next = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_subshell	*subshell;

	subshell = malloc(sizeof(t_subshell));
	ft_subshell_init(subshell, SUBSHELL, env);

	return (0);
}
