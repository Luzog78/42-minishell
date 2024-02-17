/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:29:15 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 03:33:48 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parsing.h"

void	ft_wait_line(char *line, t_subshell	*subshell)
{
	while (1)
	{
		line = readline("minishell $> ");
		if (!line)
			line = ft_strdup("exit");
		if (ft_strlen(line))
			add_history(line);
		if (!ft_check_parenthesis_and_quotes(line))
		{
			free(line);
			ft_error(2, "syntax error: wrong parentheses or quotes", NULL);
			g_exit = 2;
			continue ;
		}
		ft_parse(subshell, line);
		free(line);
		if (subshell->exit_status)
		{
			ft_free_cmds(subshell->cmds);
			subshell->cmds = NULL;
			g_exit = subshell->exit_status;
			continue ;
		}
		ft_exec(subshell);
	}
}
