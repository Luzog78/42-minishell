/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 03:39:13 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/25 12:33:54 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minish.h"
# include "builtins.h"

int	ft_dup_infiles(char *infile);
int	ft_dup_outfiles(t_out *outfiles);
int	ft_heredoc(char *limiter);
int	ft_stdin(t_stdin_lst *stdin);
int	ft_pipe(t_subshell *cmds);
int	ft_execve_bin(char **argv, char **env);

#endif
