/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 06:19:36 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/14 06:21:05 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minish.h"

void	manage_cmds(t_subshell *cmds, int pipe[2]);
void	ft_sig_nothing(int sig);
void	ft_sig_stop(int sig);
void	ft_sig_handling(int sig);

#endif