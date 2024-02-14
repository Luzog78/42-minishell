/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:59:05 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/14 04:03:03 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	ft_export_error(int *exit_status, char **var)
{
	if (!*var || !bi_check_var(*var))
	{
		if (!*var)
			*var = "(null)";
		ft_printf_err(
			"minishell: export: `%s': not a valid identifier\n", *var);
		if (*var)
			free(*var);
		*var = NULL;
		*exit_status = 1;
	}
}

static t_bool	ft_export_args(char **argv, t_subshell *cmds,
	int *exit_status, char **var)
{
	while (*argv)
	{
		if (**argv == '-')
		{
			ft_printf_err(
				"minishell: export: the flag `%s' is not handled\n", *argv);
			*exit_status = 2;
			argv++;
			continue ;
		}
		*var = bi_get_var(cmds->env, *argv);
		ft_export_error(exit_status, var);
		if (*var)
		{
			if (bi_is_var_in_env(*var, cmds->env))
				cmds->env = bi_update_env(*var, cmds->env);
			else
				cmds->env = bi_add_env(*var, cmds->env);
			if (cmds->env == NULL)
				return (TRUE);
		}
		free(*var);
		argv++;
	}
	return (FALSE);
}

int	ft_export(char **argv, t_subshell *cmds)
{
	char	*var;
	int		exit_status;

	exit_status = 0;
	if (!argv[0])
		bi_printenv(cmds->env);
	else if (ft_export_args(argv, cmds, &exit_status, &var))
		exit_status = 1;
	return (exit_status);
}
