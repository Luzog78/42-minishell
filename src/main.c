/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 01:24:46 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/08 10:41:25 by ysabik           ###   ########.fr       */
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

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

int	main(int argc, char **argv, char **env)
{
	t_subshell	*subshell;
	char		*line;

	(void)argc;
	(void)argv;
	subshell = ft_calloc(sizeof(t_subshell), 1);
	if (!subshell)
		return (1);
	ft_subshell_init(subshell, SUBSHELL, env);
	ft_sig_init(&subshell);
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
			ft_free_subshell(subshell->cmds);
			subshell->cmds = NULL;
			g_exit = subshell->exit_status;
			continue ;
		}
		ft_exec(subshell);
		// ft_free_subshell(subshell->cmds);
		subshell->cmds = NULL;
	}
	ft_free_subshell(subshell);
	return (g_exit);
}
