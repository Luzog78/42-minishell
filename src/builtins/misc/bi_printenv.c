/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_printenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:32:17 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 10:34:28 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	bi_printenv(char **env)
{
	int		i;
	char	**sorted_env;

	i = 0;
	while (env[i])
		i++;
	sorted_env = ft_calloc(sizeof(char *), (i + 1));
	if (!sorted_env)
		return ;
	i = 0;
	ft_arr_char_cpy(env, sorted_env);
	sorted_env = ft_sort_env(sorted_env);
	bi_add_double_quotes(sorted_env);
	while (sorted_env[i] && ft_strchr(sorted_env[i], '='))
		printf("declare -x %s\n", sorted_env[i++]);
	sorted_env[i] = NULL;
	i = 0;
	while (sorted_env[i])
	{
		free(sorted_env[i]);
		i++;
	}
	free(sorted_env);
}
