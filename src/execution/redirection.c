/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:15:30 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/13 03:26:29 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtins.h"

int	ft_dup_infiles(char *infile, char **env)
{
	int		fd;
	char	*path;

	path = ft_get_bash_string(infile, env);
	if (!path)
		return (-1);
	fd = open(path, O_RDONLY);
	free(path);
	if (fd == -1)
	{
		perror("minishell");
		return (-1);
	}
	return (fd);
}

int	ft_dup_outfiles(t_out *outfiles, char **env)
{
	int		fd;
	char	*path;

	while (outfiles)
	{
		fd = -1;
		path = ft_get_bash_string(outfiles->to, env);
		if (outfiles->type == REPLACE)
			fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (outfiles->type == APPEND)
			fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("minishell");
			return (1);
		}
		free(path);
		dup2(fd, outfiles->from);
		close(fd);
		outfiles = outfiles->next;
	}
	return (0);
}

char	*ft_get_temp_filename(void)
{
	char	*filename;
	char	*random;
	int		i;

	i = 0;
	filename = ft_calloc(sizeof(char), 15);
	if (!filename)
		return (NULL);
	ft_strcpy(filename, "/tmp/minishell");
	while (access(filename, F_OK) != -1)
	{
		free(filename);
		random = ft_itoa(i);
		filename = ft_calloc(sizeof(char), 15 + ft_strlen(random));
		if (!filename)
			return (NULL);
		ft_strcpy(filename, "/tmp/minishell");
		ft_strcat(filename, random);
		free(random);
		i++;
	}
	return (filename);
}

char	*get_right_limiter(char *limiter, t_bool *is_formattable)
{
	char	*new;
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	*is_formattable = TRUE;
	new = ft_calloc(sizeof(char), 1);
	if (!new)
		return (NULL);
	while (limiter[i])
	{
		if (limiter[i] == '\'' || limiter[i] == '\"')
		{
			*is_formattable = FALSE;
			quote = limiter[i];
			i++;
			while (limiter[i] && limiter[i] != quote)
			{
				new = realloc(new, ft_strlen(new) + 2);
				if (!new)
					return (NULL);
				new[ft_strlen(new) + 1] = 0;
				new[ft_strlen(new)] = limiter[i];
				i++;
			}
		}
		else if (limiter[i] == '$' && (limiter[i + 1] == '_'
				|| (limiter[i + 1] >= 'a' && limiter[i + 1] <= 'z')
				|| (limiter[i + 1] >= 'A' && limiter[i + 1] <= 'Z')))
		{
			new = realloc(new, ft_strlen(new) + 2);
			if (!new)
				return (NULL);
			new[ft_strlen(new) + 1] = 0;
			new[ft_strlen(new)] = limiter[i];
			i++;
			while (limiter[i] && (limiter[i] == '_'
				|| (limiter[i] >= 'a' && limiter[i] <= 'z')
				|| (limiter[i] >= 'A' && limiter[i] <= 'Z')
				|| (limiter[i] >= '0' && limiter[i] <= '9')))
			{
				new = realloc(new, ft_strlen(new) + 2);
				if (!new)
					return (NULL);
				new[ft_strlen(new) + 1] = 0;
				new[ft_strlen(new)] = limiter[i];
				i++;
			}
			continue ;
		}
		else
		{
			*is_formattable = FALSE;
			new = realloc(new, ft_strlen(new) + 2);
			if (!new)
				return (NULL);
			new[ft_strlen(new) + 1] = 0;
			new[ft_strlen(new)] = limiter[i];
		}
		i++;
	}
	free(limiter);
	return (new);
}

int	ft_heredoc(t_subshell *cmds, t_stdin_lst *stdin, char **env)
{
	char	*line;
	t_bool	is_formattable;
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
	{
		perror("minishell");
		return (-1);
	}
	stdin->value = get_right_limiter(stdin->value, &is_formattable);
	pid = fork();
	if (!pid)
	{
		ft_sig_init(2);
		while (1)
		{
			line = readline("> ");
			if (!line || !ft_strcmp(line, stdin->value) || g_exit)
			{
				free(line);
				break ;
			}
			if (is_formattable)
				line = ft_get_bash_string(line, env);
			if (line)
				ft_putstr_fd(line, pipefd[1]);
			ft_putstr_fd("\n", pipefd[1]);
			free(line);
		}
		close(pipefd[0]);
		close(pipefd[1]);
		ft_free_cmds(ft_get_parent(cmds));
		exit(0);
	}
	else
	{
		waitpid(-1, &status, 0);
		ft_sig_exit(status);
		close(pipefd[1]);
	}
	return (pipefd[0]);
}

int	ft_stdin(t_subshell *cmds, t_stdin_lst *stdin)
{
	int	fd;

	fd = 0;
	while (stdin)
	{
		if (fd != 0)
			close(fd);
		if (stdin->type == HEREDOC)
			fd = ft_heredoc(cmds, stdin, cmds->env);
		else if (stdin->type == INFILE)
			fd = ft_dup_infiles(stdin->value, cmds->env);
		stdin = stdin->next;
	}
	if (fd == -1)
	{
		g_exit = 1;
		return (g_exit);
	}
	dup2(fd, 0);
	close(fd);
	return (g_exit);
}
