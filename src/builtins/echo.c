/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:52:01 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/27 14:33:25 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_echo(char **argv)
{
	int		i;
	pid_t	pid;

	i = 1;
	pid = fork();
	if (pid == 0)
	{
		if (ft_strcmp(argv[1], "-n") == 0)
			i++;
		while (argv[i])
		{
			printf("%s", argv[i]);
			if (argv[i + 1])
				printf(" ");
			i++;
		}
		if (ft_strcmp(argv[1], "-n") != 0)
			printf("\n");
		//freeall
		exit(0);
	}
	return (0);
}
