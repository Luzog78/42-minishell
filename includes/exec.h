/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 03:39:13 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/17 04:24:13 by bcarolle         ###   ########.fr       */
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

/* ***************************** */
/* ********  Executing  ******** */
/* ***************************** */

void	ft_exec_cmd(t_subshell *cmds);
void	ft_exec_subshell(t_subshell *subshell);
int		ft_execve_bin(char **argv, t_subshell *cmds);

/* ***************************** */
/* ********  Wildcards  ******** */
/* ***************************** */

void	ft_append_wildcard(char ***args, char *str, char **env);
void	wc_tokenize(t_wc_token *tk, char *wc);
t_bool	wc_is_wildcard(char *str);
t_bool	wc_allow(char *file, char *str);
t_bool	wc_allow_start(t_wc_token *tk, char *file);
t_bool	wc_allow_end(t_wc_token *tk, char *file);
t_bool	wc_allow_middle(t_wc_token *tk, char *file);

/* ***************************** */
/* ********  Redirection  ****** */
/* ***************************** */

char	*ft_get_right_limiter(char *limiter, t_bool *is_formattable);
int		ft_heredoc(t_subshell *cmds, t_stdin_lst *stdin, char **env);
int		ft_stdin(t_subshell *cmds, t_stdin_lst *stdin);
int		ft_dup_infiles(char *infile, char **env);
int		ft_dup_outfiles(t_out *outfiles, char **env);

/* ***************************** */
/* ********  Utilities  ******** */
/* ***************************** */

int		ft_allow_next_cmd(t_subshell *cmds);
void	ft_args_append_str(char ***args, char *str, char **env);
void	ft_args_realloc(char ***args, char *str);
void	ft_args_reallocs(char ***args, t_str_lst **lst);
char	**ft_str_lst_to_args(t_str_lst *lst, char **env);

#endif
