/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 00:53:11 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/08 03:14:26 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H
# define MINISH_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <termcap.h>
# include <errno.h>

# ifndef MAIN_FILE

extern int	g_exit;

# else
#  undef MINISH_H
# endif

# ifndef CONTENTS
#  define CONTENTS

#  undef FALSE
#  undef TRUE

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef enum e_link
{
	PIPE,
	PIPE_AND,
	OR,
	AND,
	NONE
}	t_link;

typedef enum e_cmd_type
{
	UNDEFINED,
	COMMAND,
	SUBSHELL
}	t_cmd_type;

typedef enum e_out_type
{
	NO_OUT,
	REPLACE,
	APPEND
}	t_out_type;

typedef enum e_stdin_type
{
	NO_IN,
	HEREDOC,
	INFILE
}	t_stdin_type;

typedef struct s_out
{
	int					from;
	char				*to;
	t_out_type			type;
	struct s_out		*next;
}	t_out;

typedef struct s_stdin_lst
{
	char				*value;
	t_stdin_type		type;
	struct s_stdin_lst	*next;
}	t_stdin_lst;

typedef struct s_str_lst
{
	char				*value;
	struct s_str_lst	*next;
}	t_str_lst;

typedef struct s_subshell
{
	t_cmd_type			type;
	int					exit_status;
	pid_t				pid;

	// SUBSHELL
	char				**env;
	struct s_subshell	*cmds;

	// COMMAND
	t_str_lst			*argv;
	t_stdin_lst			*stdin;
	t_out				*outfiles;

	t_link				link;
	int					pipe_read_end;
	int					stdin_fd;
	int					stdout_fd;
	struct s_subshell	*parent;
	struct s_subshell	*prev;
	struct s_subshell	*next;
}	t_subshell;

void		ft_parse(t_subshell *subshell, char *str);
void		ft_subshell_init(t_subshell *subshell, t_cmd_type type, char **env);
t_bool		ft_check_parenthesis_and_quotes(char *str);
void		ft_exec(t_subshell *subshell);
void		ft_exec_subshell(t_subshell *subshell);
void		ft_exec_cmd(t_subshell *cmds);
char		*ft_strdup(char *str);
size_t		ft_strlen(const char *str);
int			ft_strcmp(char *s1, char *s2);
char		**ft_env_cpy(char **env);
char		*ft_strcpy(char *dst, const char *src);
void		ft_strcat(char *dest, char *str);
void		ft_putstr_fd(char *str, int fd);
char		*ft_strstr(const char *haystack, const char *needle);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strncmp(char *s1, char *s2, int n);
void		free_cmds(t_subshell *subshell);
char		**ft_free_char_array(char **array);
char		**ft_env_owrite(char **env, char **new_env);
char		**ft_split(char *str, char c);
int			ft_error(int err, char *str, t_subshell *subshell_to_free);
void		ft_free_subshell(t_subshell *subshell);
char		*ft_getenv(char *str, char **env);
char		*ft_get_bash_string(char *str, char **env);
char		*ft_substr(char *s, int start, int len);
char		*ft_strchr(const char *s, int c);
void		ft_sig_init(t_subshell **master);
char		*get_next_line(int fd, char *limiter);
t_subshell	*ft_get_parent(t_subshell *cmds);
t_subshell	*ft_get_nearest_subshell(t_subshell *cmds);
char		*ft_get_value_from_env(char *key, char **env);
void	ft_print_err(char *str);
void	ft_printf_err(char *str, char *err);
void	ft_printf_err2(char *str, char *err1, char *err2);

# endif
#endif
