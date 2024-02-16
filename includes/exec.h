/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 03:39:13 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/17 00:53:58 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "builtins.h"

typedef struct s_heredoc
{
	t_subshell	*cmds;
	t_stdin_lst	*stdin;
	char		**env;
	int			*pipefd;
	t_bool		is_formattable;
}	t_heredoc;

typedef struct s_wc_token
{
	char		*start;
	char		*end;
	t_str_lst	*tks;
}	t_wc_token;

int		ft_dup_infiles(char *infile, char **env);
int		ft_dup_outfiles(t_out *outfiles, char **env);
int		ft_heredoc(t_subshell *cmds, t_stdin_lst *stdin, char **env);
char	*ft_get_right_limiter(char *limiter, t_bool *is_formattable);
int		ft_stdin(t_subshell *cmds, t_stdin_lst *stdin);
int		ft_execve_bin(char **argv, t_subshell *cmds);
void	ft_exec_cmd(t_subshell *cmds);
void	ft_exec_subshell(t_subshell *subshell);
int		allow_next(t_subshell *cmds);
char	**ft_lststr_to_char_array(t_str_lst *lst, char **env);
size_t	ft_lstsize(t_str_lst *lst);
void	ft_append_wildkartttt(char ***args, char *str, char **env);
t_bool	ft_is_wildcard(char *str);
t_bool	ft_wildcard_allow(char *file, char *str);
void	ft_wc_tokenize(t_wc_token *tk, char *wc);
t_bool	ft_wc_allow_start(t_wc_token *tk, char *file);
t_bool	ft_wc_allow_end(t_wc_token *tk, char *file);
t_bool	ft_wc_allow_middle(t_wc_token *tk, char *file);

#endif
