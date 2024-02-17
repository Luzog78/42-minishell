/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_allow_middle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 02:24:23 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 02:24:37 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_bool	wc_allow_middle(t_wc_token *tk, char *file)
{
	t_str_lst	*cursor;
	char		*tmp;

	if (!tk->tks)
		return (TRUE);
	file = ft_strdup(file);
	if (!file)
		return (FALSE);
	if (tk->start)
	{
		tmp = file;
		file = ft_substr(file, ft_strlen(tk->start),
				ft_strlen(file) - ft_strlen(tk->start));
		free(tmp);
		if (!file)
			return (FALSE);
	}
	if (tk->end)
	{
		tmp = file;
		file = ft_substr(file, 0, ft_strlen(file) - ft_strlen(tk->end));
		free(tmp);
		if (!file)
			return (FALSE);
	}
	tmp = file;
	cursor = tk->tks;
	while (cursor)
	{
		if (!cursor->value)
			continue ;
		if (!*file)
		{
			free(tmp);
			return (FALSE);
		}
		if (ft_strncmp(file, cursor->value, ft_strlen(cursor->value)))
		{
			file++;
			continue ;
		}
		file++;
		cursor = cursor->next;
	}
	free(tmp);
	return (TRUE);
}
