/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_append_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 02:36:45 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 02:36:58 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_args_append_str(char ***args, char *str, char **env)
{
	char	*new;

	if (!str)
		return ;
	new = ft_get_bash_string(str, env, TRUE);
	if (!new)
	{
		free(str);
		return ;
	}
	if (!wc_is_wildcard(new))
	{
		free(new);
		new = ft_get_bash_string(str, env, FALSE);
		free(str);
		if (new)
			ft_args_realloc(args, new);
		free(new);
		return ;
	}
	free(new);
	ft_append_wildcard(args, str, env);
}
