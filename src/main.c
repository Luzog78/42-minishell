/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 01:24:46 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/15 07:49:52 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

char	*ft_strdup(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	while (str[i])
		i++;
	new_str = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}

char	**ft_env_cpy(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

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
	char		*line;

	(void)argc;
	(void)argv;
	subshell = malloc(sizeof(t_subshell));
	ft_subshell_init(subshell, SUBSHELL, env);
	(void)subshell;
	(void)line;
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
		//exec commands
	}
	return (0);
}
