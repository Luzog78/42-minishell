/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:58:25 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/17 08:53:47 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(char **argv, t_subshell *cmds)
{
	char	*pwd;

	(void)argv;
	(void)cmds;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("minishell");
		return (1);
	}
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(pwd);
	return (0);
}
