/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_var_concat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:34:30 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/14 03:34:43 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*bi_var_concat(char *var, char **env)
{
	char	*var_name;
	char	*var_value;
	char	*new_var_value;
	char	*new_var;
	int		i;

	i = 0;
	while (var[i] && var[i] != '+')
		i++;
	var_name = ft_substr(var, 0, i);
	var_value = ft_getenv(var_name, env);
	new_var_value = ft_substr(var, i + 2, ft_strlen(var) - i - 2);
	new_var = ft_strjoin(var_name, "=");
	free(var_name);
	var_name = ft_strjoin(new_var, var_value);
	free(new_var);
	new_var = ft_strjoin(var_name, new_var_value);
	free(var_name);
	free(new_var_value);
	return (new_var);
}
