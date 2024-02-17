/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_allow_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 02:24:01 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 02:24:09 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_bool	wc_allow_end(t_wc_token *tk, char *file)
{
	return (!tk->end || !ft_strncmp(file + ft_strlen(file)
			- ft_strlen(tk->end), tk->end, ft_strlen(tk->end)));
}
