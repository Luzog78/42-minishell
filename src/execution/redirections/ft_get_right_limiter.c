/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_right_limiter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 06:52:51 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/14 07:09:01 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_bool	ft_r_quote(char *limiter, char **new,
	char *quote, int *i)
{
	*quote = limiter[*i];
	(*i)++;
	while (limiter[*i] && limiter[*i] != *quote)
	{
		*new = realloc(*new, ft_strlen(*new) + 2);
		if (!*new)
			break ;
		(*new)[ft_strlen(*new) + 1] = 0;
		(*new)[ft_strlen(*new)] = limiter[*i];
		(*i)++;
	}
	(*i)++;
	return (FALSE);
}

static t_bool	ft_r_text(char *limiter, char **new, int *i)
{
	*new = realloc(*new, ft_strlen(*new) + 2);
	if (!*new)
		return (FALSE);
	(*new)[ft_strlen(*new) + 1] = 0;
	(*new)[ft_strlen(*new)] = limiter[*i];
	(*i)++;
	return (FALSE);
}

static void	ft_r_value(char *limiter, char **new, int *i)
{
	*new = realloc(*new, ft_strlen(*new) + 2);
	if (!*new)
		return ;
	(*new)[ft_strlen(*new) + 1] = 0;
	(*new)[ft_strlen(*new)] = limiter[*i];
	(*i)++;
	while (limiter[*i] && (limiter[*i] == '_'
			|| (limiter[*i] >= 'a' && limiter[*i] <= 'z')
			|| (limiter[*i] >= 'A' && limiter[*i] <= 'Z')
			|| (limiter[*i] >= '0' && limiter[*i] <= '9')))
	{
		*new = realloc(*new, ft_strlen(*new) + 2);
		if (!*new)
			return ;
		(*new)[ft_strlen(*new) + 1] = 0;
		(*new)[ft_strlen(*new)] = limiter[*i];
		(*i)++;
	}
}

char	*ft_get_right_limiter(char *limiter, t_bool *is_formattable)
{
	char	*new;
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	*is_formattable = TRUE;
	new = ft_calloc(sizeof(char), 1);
	if (!new)
		return (NULL);
	while (limiter[i])
	{
		if (limiter[i] == '\'' || limiter[i] == '\"')
			*is_formattable = ft_r_quote(limiter, &new, &quote, &i);
		else if (limiter[i] == '$' && (limiter[i + 1] == '_'
				|| (limiter[i + 1] >= 'a' && limiter[i + 1] <= 'z')
				|| (limiter[i + 1] >= 'A' && limiter[i + 1] <= 'Z')))
			ft_r_value(limiter, &new, &i);
		else
			*is_formattable = ft_r_text(limiter, &new, &i);
	}
	free(limiter);
	return (new);
}
