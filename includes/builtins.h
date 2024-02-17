/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:16:14 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/17 08:53:01 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "utils.h"

/* ***************************** */
/* ********  Built-ins  ******** */
/* ***************************** */

int		ft_echo(char **argv, t_subshell *cmds);
int		ft_cd(char **argv, t_subshell *cmds);
int		ft_env(char **argv, t_subshell *cmds);
int		ft_exit(char **argv, t_subshell *cmds);
int		ft_export(char **argv, t_subshell *cmds);
int		ft_pwd(char **argv, t_subshell *cmds);
int		ft_unset(char **argv, t_subshell *cmds);

/* ********************************** */
/* ********  Miscellaneaous  ******** */
/* ********************************** */

void	bi_add_double_quotes(char **env);
char	**bi_add_env(char *new_var, char **env);
int		bi_check_var(char *var);
char	*bi_get_var(char **env, char *argv);
int		bi_is_var_in_env(char *var, char **env);
void	bi_printenv(char **env);
char	**bi_update_env(char *new_var, char **env);
char	*bi_var_concat(char *var, char **env);

#endif
