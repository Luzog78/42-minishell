/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 01:24:46 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/17 03:35:32 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MAIN_FILE
#include "minish.h"
#undef MAIN_FILE
#include "utils.h"

int	g_exit = 0;

int	main(int argc, char **argv, char **env)
{
	t_subshell	*subshell;

	(void)argc;
	(void)argv;
	subshell = ft_calloc(sizeof(t_subshell), 1);
	if (!subshell)
		return (1);
	ft_subshell_init(subshell, SUBSHELL, env);
	ft_sig_init(1, subshell, NULL);
	ft_wait_line(NULL, subshell);
	ft_free_cmds(subshell);
	return (g_exit);
}
