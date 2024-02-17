/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_add_double_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:13:30 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 10:27:55 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	ft_create_new_line(char **env, char *tmp, int i, int k)
{
	int	j;

	j = 0;
	while (env[i][j])
	{
		if (env[i][j] == '=')
		{
			tmp[j] = env[i][j];
			tmp[++j] = '"';
			k = j;
			k++;
			while (env[i][j])
			{
				if (env[i][j] == '"' || env[i][j] == '$' || env[i][j] == '\\')
					tmp[k++] = '\\';
				tmp[k++] = env[i][j++];
			}
			tmp[k] = '"';
		}
		else
		{
			tmp[j] = env[i][j];
			j++;
		}
	}
}

static void	ft_format_line(char **env, int i)
{
	int		j;
	int		k;
	char	*tmp;

	j = 0;
	while (env[i][j] && env[i][j] != '=')
		j++;
	k = 0;
	while (env[i][j])
	{
		if (env[i][j] == '"' || env[i][j] == '$' || env[i][j] == '\\')
			k++;
		j++;
	}
	tmp = ft_calloc(sizeof(char), ft_strlen(env[i]) + k + 3);
	if (!tmp)
		return ;
	ft_create_new_line(env, tmp, i, k);
	free(env[i]);
	env[i] = tmp;
}

void	bi_add_double_quotes(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_format_line(env, i);
		i++;
	}
}
