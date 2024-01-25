/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:58:25 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/25 11:46:24 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(char **env)
{
	char	*pwd;

	(void)env;
	pwd = getenv("PWD");
	if (!pwd)
	{
		perror("minishell");
		return (1);
	}
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (1);
}
