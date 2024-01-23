/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:52:40 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/23 18:23:22 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_cd(char **argv)
{
	char	*home;

	if (argv[1] == NULL)
	{
		home = getenv("HOME");
		if (chdir(home) == -1)
		{
			perror("minishell");
			free(home);
			return (1);
		}
		free(home);
		return (0);
	}
	if (chdir(argv[1]) == -1)
	{
		perror("minishell");
		return (1);
	}
	return (0);
}
