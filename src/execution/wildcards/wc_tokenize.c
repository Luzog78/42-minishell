/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 23:43:33 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 04:24:28 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	wc_tokenize(t_wc_token *tk, char *wc)
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
