/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 22:46:42 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/17 18:30:52 by bcarolle         ###   ########.fr       */
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
	while (lst)
	{
		array[i] = ft_strdup(lst->value);
		i++;
		lst = lst->next;
	}
	array[i] = NULL;
	return (array);
}

int	ft_execve_bin(char **argv, char **env)
{
	
	if (execve(argv[0], argv, env) == -1)
	{
		perror("minishell");
		return (1);
	}
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
		exit_status = ft_cd(argv, cmds->env);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		exit_status = ft_pwd(argv, cmds->env);
	else if (ft_strcmp(argv[0], "export") == 0)
		exit_status = ft_export(argv, cmds->env);
	else if (ft_strcmp(argv[0], "unset") == 0)
		exit_status = ft_unset(argv, cmds->env);
	else if (ft_strcmp(argv[0], "env") == 0)
		exit_status = ft_env(cmds->env);
	else if (ft_strcmp(argv[0], "exit") == 0)
		exit_status = ft_exit(argv);
	else
		exit_status = ft_execve_bin(argv, cmds->env);
	//ft_free_char_array(argv);
	return (exit_status);
}

void	ft_exec_cmd(t_subshell *cmds)
{
	if (!cmds->exit_status && cmds->stdin)
		cmds->exit_status = ft_stdin(cmds->stdin);
	if (!cmds->exit_status && cmds->outfiles)
		cmds->exit_status = ft_dup_outfiles(cmds->outfiles);
	if (!cmds->exit_status && cmds->argv)
		cmds->exit_status = ft_execve(cmds);
	if (!cmds->next)
		return ;
	if (cmds->next->type == COMMAND)
		ft_exec_cmd(cmds->next);
	else if (cmds->next->type == SUBSHELL)
		ft_exec_subshell(cmds->next);
}

void	ft_exec_subshell(t_subshell *subshell)
{
	if (!subshell)
		return ;
	if (subshell->next->type == COMMAND)
		ft_exec_cmd(subshell->next);
	else if (subshell->next->type == SUBSHELL)
		ft_exec_subshell(subshell->next);
}

void	ft_exec(t_subshell *subshell)
{
	ft_exec_cmd(subshell->cmds);
	ft_subshell_init(subshell, SUBSHELL, subshell->env);
}
