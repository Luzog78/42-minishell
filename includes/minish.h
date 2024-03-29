/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 00:53:11 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/17 03:35:40 by ysabik           ###   ########.fr       */
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

/**
 * @param	env			Reserved for the SUBSHELL type
 * @param	cmds		Reserved for the SUBSHELL type
 *
 * @param	argv		Reserved for the COMMAND type
 * @param	stdin		Reserved for the COMMAND type
 * @param	outfiles	Reserved for the COMMAND type
*/
typedef struct s_subshell
{
	t_cmd_type			type;
	int					exit_status;
	pid_t				pid;

	char				**env;
	struct s_subshell	*cmds;

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

void	ft_parse(t_subshell *subshell, char *str);
void	ft_exec(t_subshell *subshell);
void	ft_sig_init(int mode, t_subshell *cmds, int pipe[2]);
void	ft_sig_exit(int status);

void	ft_wait_line(char *line, t_subshell	*subshell);

# endif
#endif
