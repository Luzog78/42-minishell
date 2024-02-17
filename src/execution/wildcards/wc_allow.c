/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_allow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 02:25:38 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 02:25:48 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_bool	wc_allow(char *file, char *str)
{
	t_wc_token	tk;
	t_bool		ret;

	tk = (t_wc_token){0};
	wc_tokenize(&tk, str);
	ret = TRUE;
	if (!wc_allow_start(&tk, file)
		|| !wc_allow_end(&tk, file)
		|| !wc_allow_middle(&tk, file))
		ret = FALSE;
	free(tk.start);
	free(tk.end);
	ft_free_str_lst(tk.tks);
	return (ret);
}
