/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 03:39:13 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/08 01:22:41 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minish.h"
# include "builtins.h"

int		ft_dup_infiles(char *infile);
int		ft_dup_outfiles(t_out *outfiles);
int		ft_heredoc(char *limiter, char **env);
int		ft_stdin(t_stdin_lst *stdin, char **env);
int		ft_pipe(t_subshell *cmds);
int		ft_execve_bin(char **argv, t_subshell *cmds);
int		ft_execve_bin_piped(char **argv, t_subshell *cmds);
void	ft_exec_cmd(t_subshell *cmds);
void	ft_exec_subshell(t_subshell *subshell);
int		allow_next(t_subshell *cmds);
char	**ft_lststr_to_char_array(t_str_lst *lst, char **env);
size_t	ft_lstsize(t_str_lst *lst);

#endif
