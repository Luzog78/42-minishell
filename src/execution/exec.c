/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 22:46:42 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/27 21:55:15 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

size_t	ft_lstsize(t_str_lst *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

char	**ft_lststr_to_char_array(t_str_lst *lst)
{
	char	**array;
	int		i;

	i = 0;
	array = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!array)
		return (NULL);
	while (lst)
	{
		array[i] = ft_strdup(lst->value);
		i++;
		lst = lst->next;
	}
	array[i] = NULL;
	return (array);
}

int	allow_next(t_subshell *cmds)
{
	if (cmds->link == PIPE || cmds->link == PIPE_AND)
		return (1);
	if (cmds->link == AND && cmds->exit_status == 0)
		return (1);
	if (cmds->link == OR && cmds->exit_status != 0)
		return (1);
return (0);
}

int	ft_execve(t_subshell *cmds)
{
	char	**argv;
	int		exit_status;

	argv = ft_lststr_to_char_array(cmds->argv);
	exit_status = 0;
	if (ft_strcmp(argv[0], "echo") == 0)
		exit_status = ft_echo(argv);
	else if (ft_strcmp(argv[0], "cd") == 0)
		exit_status = ft_cd(argv, cmds);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		exit_status = ft_pwd(cmds->env);
	else if (ft_strcmp(argv[0], "export") == 0)
		exit_status = ft_export(argv[1], cmds);
	else if (ft_strcmp(argv[0], "unset") == 0)
		exit_status = ft_unset(argv, cmds);
	else if (ft_strcmp(argv[0], "env") == 0)
		exit_status = ft_env(cmds->env);
	else if (ft_strcmp(argv[0], "exit") == 0)
		exit_status = ft_exit();
	else
		exit_status = ft_execve_bin(argv, cmds->env);
	waitpid(-1, NULL, 0);
	ft_free_char_array(argv);
	return (exit_status);
}

void	ft_exec_cmd(t_subshell *cmds)
{
	if (!cmds->exit_status && cmds->stdin)
		cmds->exit_status = ft_stdin(cmds->stdin);
	if (!cmds->exit_status && cmds->outfiles)
		cmds->exit_status = ft_dup_outfiles(cmds->outfiles);
	if (!cmds->exit_status && cmds->link == PIPE)
		cmds->exit_status = ft_pipe(cmds);
	if (!cmds->exit_status && cmds->argv)
		cmds->exit_status = ft_execve(cmds);
	if (cmds->next == NULL)
		return ;
	cmds->next->env = ft_env_cpy(cmds->env);
	if (cmds->next->type == COMMAND && allow_next(cmds))
		ft_exec_cmd(cmds->next);
	if (cmds->next->type == SUBSHELL && allow_next(cmds))
		ft_exec_subshell(cmds->next);
}

void	ft_exec_subshell(t_subshell *subshell)
{
	pid_t	pid;

	if (!subshell)
		return ;
	pid = fork();
	if (pid == 0)
	{
		if (subshell->cmds && subshell->cmds->type == COMMAND)
		{
			subshell->cmds->env = ft_env_cpy(subshell->env);
			ft_exec_cmd(subshell->cmds);
		}
		else if (subshell->cmds && subshell->cmds->type == SUBSHELL)
		{
			subshell->cmds->env = ft_env_cpy(subshell->env);
			ft_exec_subshell(subshell->cmds);
		}
		free_all(subshell, 0);
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
	if (subshell->next && subshell->next->type == COMMAND
		&& allow_next(subshell))
	{
		subshell->next->env = ft_env_cpy(subshell->env);
		ft_exec_cmd(subshell->next);
	}
	else if (subshell->next && subshell->next->type == SUBSHELL
		&& allow_next(subshell))
	{
		subshell->next->env = ft_env_cpy(subshell->env);
		ft_exec_subshell(subshell->next);
	}
}

void	ft_exec(t_subshell *subshell)
{
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
	free_all(subshell, 0);
}
