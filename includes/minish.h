/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 00:53:11 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/15 02:36:14 by bcarolle         ###   ########.fr       */
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
	COMMAND,
	SUBSHELL
}	t_cmd_type;

typedef enum e_out_type
{
	REPLACE,
	APPEND
}	t_out_type;

typedef struct s_out
{
	int					from;
	char				*to;
	t_out_type			type;
	struct s_out		*next;
}	t_out;

typedef struct s_subshell
{
	t_cmd_type			type; // 1

	// SUBSHELL
	char				**env;
	int					exit_status;
	struct s_subshell	*cmds; // NULL

	// COMMAND
	char				**argv;
	char				*infile;
	t_out				*outfiles;
	char				*heredoc;

	t_link				link; // NONE
	struct s_subshell	*next; //NULL
}	t_subshell;

#endif
