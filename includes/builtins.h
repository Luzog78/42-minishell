/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:16:14 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/14 04:02:02 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "utils.h"

int		ft_echo(char **argv, char **env);
int		ft_cd(char **argv, t_subshell *cmds);
int		ft_env(char **argv, char **env);
int		ft_exit(t_subshell *cmds, char **argv);
int		ft_export(char **argv, t_subshell *cmds);
int		ft_pwd(char **env);
int		ft_unset(char **argv, t_subshell *cmds);

int		bi_is_var_in_env(char *var, char **env);
char	**bi_update_env(char *new_var, char **env);
char	**bi_add_env(char *new_var, char **env);

void	bi_add_double_quotes(char **env);
char	**bi_add_env(char *new_var, char **env);
int		bi_check_var(char *var);
char	*bi_get_var(char **env, char *argv);
int		bi_is_var_in_env(char *var, char **env);
void	bi_printenv(char **env);
char	**bi_update_env(char *new_var, char **env);
char	*bi_var_concat(char *var, char **env);

#endif
