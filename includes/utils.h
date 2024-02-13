/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:26:06 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/13 03:42:02 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minish.h"


/* Execution Utils Functions */
char		**ft_env_owrite(char **env, char **new_env);
char		**ft_env_cpy(char **env);
t_str_lst	*ft_free_str_lst(t_str_lst *lst);
t_stdin_lst	*ft_free_stdin_lst(t_stdin_lst *lst);
t_out		*ft_free_out_lst(t_out *lst);
char		**ft_free_char_array(char **array);
void		ft_free_cmds(t_subshell *subshell);
void		ft_close_std(t_subshell *subshell);
t_subshell	*ft_get_parent(t_subshell *cmds);
char		*ft_get_value_from_env(char *key, char **env);
char		*ft_getenv(char *name, char **env);
char		*ft_get_bash_string(char *str, char **env);

/* Libft Functions */
void		*ft_calloc(size_t count, size_t size);
char		**ft_split(char *str, char c);
char		*ft_itoa(int n);
char		**ft_split(char *s, char c);
void		ft_strcat(char *dest, char *str);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strdup(char *str);
char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlen(const char *str);
int			ft_strncmp(char *s1, char *s2, int n);
char		*ft_strstr(const char *haystack, const char *needle);
char		*ft_substr(char *str, int start, int len);
char		*ft_strtrim(char *str);
int			ft_isalnum(int c);
char		*ft_get_bash_string(char *str, char **env);

/* Print Functions */
void		ft_print_err(char *str);
void		ft_printf_err(char *str, char *err);
void		ft_putstr_fd(char *str, int fd);
void		ft_perror(void);

#endif
