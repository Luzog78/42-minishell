/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:15:30 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/08 04:14:25 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtins.h"

int	ft_dup_infiles(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		return (-1);
	}
	free(infile);
	return (fd);
}

int	ft_dup_outfiles(t_out *outfiles)
{
	int	fd;

	while (outfiles)
	{
		fd = -1;
		if (outfiles->type == REPLACE)
			fd = open(outfiles->to, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (outfiles->type == APPEND)
			fd = open(outfiles->to, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("minishell");
			return (1);
		}
		dup2(fd, outfiles->from);
		close(fd);
		outfiles = outfiles->next;
	}
	return (0);
}

char	*ft_get_temp_filename(void)
{
	char	*random;

	random = ft_strdup("minishell_XXXXXX");
	return (random);
}

char	*get_right_limiter(char *limiter, t_bool *is_formattable)
{
	char	*new;
	int		i;
	char	quote;
	t_bool	dollar;

	i = 0;
	quote = 0;
	*is_formattable = TRUE;
	dollar = FALSE;
	new = calloc(sizeof(char), 1);
	if (!new)
		return (NULL);
	while (limiter[i])
	{
		if (limiter[i] == '\'' || limiter[i] == '\"')
		{
			quote = limiter[i];
			if (limiter[i + 1] != quote)
				*is_formattable = FALSE;
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
			if (!dollar)
				dollar = TRUE;
			else
				*is_formattable = FALSE;
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
	return (new);
}

int	ft_heredoc(char *limiter, char **env)
{
	int		fd;
	char	*filename;
	char	*line;
	t_bool	is_formattable;

	filename = ft_get_temp_filename();
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell");
		return (-1);
	}
	limiter = get_right_limiter(limiter, &is_formattable);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, limiter) || g_exit)
		{
			free(line);
			break ;
		}
		if (is_formattable)
			line = ft_get_bash_string(line, env);
		if (line)
			ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	free(limiter);
	close(fd);
	fd = open(filename, O_RDONLY);
	unlink(filename);
	free(filename);
	if (fd == -1)
	{
		perror("minishell");
		return (-1);
	}
	return (fd);
}

int	ft_stdin(t_stdin_lst *stdin, char **env)
{
	int	fd;

	while (stdin)
	{
		if (stdin->type == HEREDOC)
			fd = ft_heredoc(stdin->value, env);
		else if (stdin->type == INFILE)
			fd = ft_dup_infiles(stdin->value);
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
