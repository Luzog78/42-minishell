/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 01:24:46 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/30 10:54:06 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MAIN_FILE
#include "minish.h"
#undef MAIN_FILE

int	g_exit = 0;

void	ft_subshell_init(t_subshell *subshell, t_cmd_type type, char **env)
{
	subshell->type = type;
	subshell->env = NULL;
	if (type == SUBSHELL)
		subshell->env = ft_env_cpy(env);
	subshell->exit_status = 0;
	subshell->cmds = NULL;
	subshell->argv = NULL;
	subshell->stdin = NULL;
	subshell->outfiles = NULL;
	subshell->link = NONE;
	subshell->next = NULL;
	subshell->pipe[0] = 0;
	subshell->pipe[1] = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_subshell	*subshell;
	char		*line;

	(void)argc;
	(void)argv;
	subshell = malloc(sizeof(t_subshell));
	if (!subshell)
		return (1);
	ft_subshell_init(subshell, SUBSHELL, env);
	while (1)
	{
		line = readline("minishell $> ");
		add_history(line);
		if (!ft_check_parenthesis_and_quotes(line))
		{
			free(line);
			ft_error("syntax error: wrong parentheses or quotes", NULL); //Print error inside ft_check_parenthesis_and_quotes
			g_exit = 2;
			continue ;
		}
		ft_parse(subshell, line);
		if (subshell->exit_status)
		{
			free(line);
			ft_free_subshell(subshell->cmds);
			subshell->cmds = NULL;
			g_exit = subshell->exit_status;
			continue ;
		}
		ft_exec(subshell);
		free(line);
		ft_free_subshell(subshell->cmds);
		subshell->cmds = NULL;
	}
	ft_free_subshell(subshell);
	return (g_exit);
}
