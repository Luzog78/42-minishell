/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 01:24:46 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/23 18:59:04 by bcarolle         ###   ########.fr       */
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
	subshell->stdin = NULL;
	subshell->outfiles = NULL;
	subshell->link = NONE;
	subshell->next = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_subshell	*subshell;
	char		*line;

	(void)argc;
	(void)argv;
	subshell = malloc(sizeof(t_subshell));
	ft_subshell_init(subshell, SUBSHELL, env);
	while (1)
	{
		line = readline("minishell $> ");
		if (!ft_check_parenthesis_and_quotes(line))
		{
			printf("error: parenthesis or quotes\n");
			continue ;
		}
		ft_parse(subshell, line);
		if (subshell->exit_status)
		{
			printf("error: parse\n");
			continue ;
		}
		ft_exec(subshell);
		add_history(line);
	}
	return (0);
}
