/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:52:01 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/17 08:53:13 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/**
 * @brief	Check if the echo command has flags
 * 				-n	Do not print the trailing newline character
 * 				-	Does nothing
 * 				(only the "-n" and the "-" flags are supported)
 * 
 * @param	argv	The arguments of the echo command
 * @param	idx		The index+1 of the last flag (modified)
 * 
 * @return	t_bool	TRUE if the -n flag is present, FALSE otherwise
 */
static t_bool	has_n_flag(char **argv, int *idx)
{
	t_bool	n_flag;
	int		j;

	n_flag = FALSE;
	*idx = 1;
	while (argv[*idx] && argv[*idx][0] == '-')
	{
		if (argv[*idx][1] == 'n')
		{
			j = 2;
			while (argv[*idx][j] == 'n')
				j++;
			if (argv[*idx][j])
				break ;
			n_flag = TRUE;
		}
		else if (argv[*idx][1])
			break ;
		(*idx)++;
	}
	return (n_flag);
}

int	ft_echo(char **argv, t_subshell *cmds)
{
	int		i;
	t_bool	n_flag;
	char	*var;

	(void)cmds;
	n_flag = has_n_flag(argv, &i);
	while (argv[i])
	{
		var = argv[i];
		write(1, var, ft_strlen(var));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n_flag)
		write(1, "\n", 1);
	return (0);
}
