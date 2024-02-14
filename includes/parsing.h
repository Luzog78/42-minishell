/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 03:39:35 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/14 04:14:24 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minish.h"

/**
 * @param	parsing_state	0: start, 1: argv, 2: redirections
*/
typedef struct s_parsing_object
{
	t_subshell	*curr_cmd;
	char		*cursor;
	t_bool		ret;

	char		*tmp;
	int			parsing_state;
}	t_parsing_object;

t_bool		ft_on_redir(t_subshell *subshell, t_parsing_object *po);
t_bool		ft_on_separator(t_subshell *subshell, t_parsing_object *po);
t_bool		ft_on_subshell(t_subshell *subshell, t_parsing_object *po);
t_bool		ft_parse_subshell(t_subshell *subshell, char **str);

t_bool		ft_check_parenthesis_and_quotes(char *str);
char		*ft_concat_lst(t_str_lst *lst);
int			ft_error(int err, char *str, t_subshell *subshell_to_free);
void		ft_free_str_list(t_str_lst *lst);
int			ft_get_next_int(char **str);
char		*ft_get_next_word(char **str);
t_out_type	ft_get_out_redirection(char *str);
t_bool		ft_is_empty(char *str);
t_bool		ft_is_next_a_fd(char *str);
t_bool		ft_is_whitespace(char c);
t_out		*ft_out_add(t_out **out, int from, char *to, t_out_type type);
void		ft_parse_redirection(t_subshell *subshell, char **str);
void		ft_set_parents(t_subshell *subshell);
void		ft_set_prevs(t_subshell *subshell);
void		ft_skip_parenthesis(char **cursor);
void		ft_skip_whitespace(char **str);
t_bool		ft_starts_with(char *str, char *prefix);
t_stdin_lst	*ft_stdin_add(t_stdin_lst **stdin, char *value, t_stdin_type type);
t_str_lst	*ft_str_lst_add(t_str_lst **lst, char *str);
t_subshell	*ft_subshell_add(t_subshell **subshll, t_cmd_type type, char **env);

#endif
