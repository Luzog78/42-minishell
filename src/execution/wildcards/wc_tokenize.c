/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 23:43:33 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 06:02:14 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

typedef struct s_wc_tokenizer
{
	char	quote;
	int		i;
	int		j;
	int		state;
}	t_wc_tokenizer;

static void	wc_on_quote(t_wc_token *token, char *wc, t_wc_tokenizer *t)
{
	if (t->j > 0)
	{
		if (t->state == 0)
			token->start = ft_substr(wc, t->i - t->j, t->j);
		else
			ft_str_lst_add_back(&token->tks, ft_substr(wc, t->i - t->j, t->j));
		t->j = 0;
	}
	t->state = 1;
	if (!t->quote)
		t->quote = wc[t->i];
	else if (t->quote == wc[t->i])
		t->quote = 0;
	t->i++;
}

static void	wc_on_star(t_wc_token *token, char *wc, t_wc_tokenizer *t)
{
	if (t->j > 0)
	{
		if (t->state == 0)
			token->start = ft_substr(wc, t->i - t->j, t->j);
		else
			ft_str_lst_add_back(&token->tks, ft_substr(wc, t->i - t->j, t->j));
		t->j = 0;
	}
	t->state = 1;
	while (wc[t->i] == '*')
		t->i++;
}

static void	wc_on_char(t_wc_tokenizer *t)
{
	if (t->state == 1)
		t->state = 2;
	t->j++;
	t->i++;
}

void	wc_tokenize(t_wc_token *token, char *wc)
{
	t_wc_tokenizer	t;

	t = (t_wc_tokenizer){0};
	while (wc[t.i])
	{
		if ((wc[t.i] == '\'' || wc[t.i] == '"')
			&& (!t.quote || t.quote == wc[t.i]))
			wc_on_quote(token, wc, &t);
		else if (wc[t.i] == '*' && !t.quote)
			wc_on_star(token, wc, &t);
		else
			wc_on_char(&t);
	}
	if (t.j > 0)
	{
		if (t.state == 0)
			token->start = ft_substr(wc, t.i - t.j, t.j);
		else
			ft_str_lst_add_back(&token->tks, ft_substr(wc, t.i - t.j, t.j));
	}
	if (t.state == 2 && token->tks)
		token->end = ft_str_lst_pop_back(&token->tks);
}
