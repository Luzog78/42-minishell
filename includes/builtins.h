/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:16:14 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/24 19:51:02 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minish.h"

int		ft_echo(char **argv);
int		ft_cd(char **argv, t_subshell *cmds);
int		ft_env(char **env);
int		ft_exit(void);
int		ft_export(char *argv, t_subshell *cmds);
int		ft_pwd(char **env);
int		ft_unset(char **argv, t_subshell *cmds);
#endif
