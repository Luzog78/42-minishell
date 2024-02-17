/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_allow_start.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 02:23:42 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 02:23:52 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_bool	wc_allow_start(t_wc_token *tk, char *file)
{
	return (!tk->start || !ft_strncmp(file, tk->start, ft_strlen(tk->start)));
}
