/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:16:14 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/23 18:06:43 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minish.h"

int		ft_echo(char **argv);
int		ft_cd(char **argv);
int		ft_env(char **env);
int		ft_exit(void);
int		ft_export(char **argv, char **env);
int		ft_pwd(char **env);
int		ft_unset(char **argv, char **env);
#endif