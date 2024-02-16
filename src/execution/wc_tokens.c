/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_tokens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 23:43:33 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 00:51:40 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_wc_tokenize(t_wc_token *tk, char *wc)
{
	char	quote;
	int		i;
	int		j;
	int		state;

	quote = 0;
	i = 0;
	j = 0;
	state = 0;
	while (wc[i])
	{
		if ((wc[i] == '\'' || wc[i] == '"')
			&& (!quote || quote == wc[i]))
		{
			if (j > 0)
			{
				if (state == 0)
					tk->start = ft_substr(wc, i - j, j);
				else
					ft_str_lst_add_back(&tk->tks, ft_substr(wc, i - j, j));
				j = 0;
			}
			state = 1;
			if (!quote)
				quote = wc[i];
			else if (quote == wc[i])
				quote = 0;
			i++;
		}
		else if (wc[i] == '*' && !quote)
		{
			if (j > 0)
			{
				if (state == 0)
					tk->start = ft_substr(wc, i - j, j);
				else
					ft_str_lst_add_back(&tk->tks, ft_substr(wc, i - j, j));
				j = 0;
			}
			state = 1;
			while (wc[i] == '*')
				i++;
		}
		else
		{
			if (state == 1)
				state = 2;
			j++;
			i++;
		}
	}
	if (j > 0)
	{
		if (state == 0)
			tk->start = ft_substr(wc, i - j, j);
		else
			ft_str_lst_add_back(&tk->tks, ft_substr(wc, i - j, j));
	}
	if (state == 2 && tk->tks)
		tk->end = ft_str_lst_pop_back(&tk->tks);
}

t_bool	ft_wc_allow_start(t_wc_token *tk, char *file)
{
	return (!tk->start || !ft_strncmp(file, tk->start, ft_strlen(tk->start)));
}

t_bool	ft_wc_allow_end(t_wc_token *tk, char *file)
{
	return (!tk->end || !ft_strncmp(file + ft_strlen(file)
			- ft_strlen(tk->end), tk->end, ft_strlen(tk->end)));
}

t_bool	ft_wc_allow_middle(t_wc_token *tk, char *file)
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

