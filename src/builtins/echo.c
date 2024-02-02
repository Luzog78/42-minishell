/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:52:01 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/02 17:29:28 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_flags(char **argv)
{
	int		i;
	int		j;

	i = 1;
	j = 1;
	while (argv[i])
	{
		if (argv[i][0] == '-')
		{
			while (argv[i][j])
			{
				if (argv[i][j] != 'n')
					return (i);
				j++;
			}
		}
		else
			return (i);
		i++;
		j = 1;
	}
	return (i);
}

int	ft_echo(char **argv, char **env)
{
	int		i;
	int		flags;
	char	*var;

	i = check_flags(argv);
	if (i < 2)
		flags = 1;
	while (argv[i])
	{
		var = ft_get_bash_string(argv[i], env);
		printf("%s", var);
		if (argv[i + 1])
			printf(" ");
		free(var);
		i++;
	}
	if (flags == 1)
		printf("\n");
	return (0);
}
