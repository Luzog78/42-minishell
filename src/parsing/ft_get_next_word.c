/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:58:37 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/13 11:13:20 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_str_lst	*ft_get_lst(char **str, int *i, char *quote, int *s_idx)
{
	t_str_lst	*lst;

	lst = NULL;
	while ((*str)[*i] && (!ft_is_whitespace((*str)[*i]) || *quote))
	{
		if (((*str)[*i] == '\'' || (*str)[*i] == '"') && !*quote)
		{
			if (*i - *s_idx > 0)
				ft_str_lst_add(&lst, ft_substr(*str, *s_idx, *i - *s_idx));
			*quote = (*str)[*i];
			*s_idx = *i;
		}
		else if (((*str)[*i] == '\'' || (*str)[*i] == '"')
			&& *quote == (*str)[*i])
		{
			*quote = 0;
			ft_str_lst_add(&lst, ft_substr(*str, *s_idx, *i + 1 - *s_idx));
			*s_idx = *i + 1;
		}
		else if (!*quote && ((*str)[*i] == '<' || (*str)[*i] == '>'
			|| (*str)[*i] == '|' || (*str)[*i] == '(' || (*str)[*i] == ')'))
			break ;
		(*i)++;
	}
	return (lst);
}

char	*ft_get_next_word(char **str)
{
	t_str_lst	*lst;
	char		quote;
	char		*word;
	int			i;
	int			start_idx;

	ft_skip_whitespace(str);
	quote = 0;
	i = 0;
	start_idx = 0;
	lst = ft_get_lst(str, &i, &quote, &start_idx);
	if (i - start_idx > 0)
		ft_str_lst_add(&lst, ft_substr(*str, start_idx, i - start_idx));
	word = ft_concat_lst(lst);
	ft_free_str_list(lst);
	(*str) += i;
	return (word);
}
