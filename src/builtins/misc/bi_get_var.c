/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_get_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:11:25 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/14 03:33:49 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*bi_get_var(char **env, char *argv)
{
	char	*var;
	int		i;

	i = 0;
	var = NULL;
	if (!bi_check_var(argv))
		return (ft_strdup(argv));
	while (argv[i])
	{
		if (argv[i] == '+' && argv[i + 1] == '=')
		{
			var = bi_var_concat(argv, env);
			break ;
		}
		i++;
	}
	if (!var)
		var = ft_strdup(argv);
	return (var);
}
