/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:15:30 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/07 17:17:55 by bcarolle         ###   ########.fr       */
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

char	*get_right_limiter(char *limiter, t_bool *quote)
{
	char	*new_limiter;
	int		i;

	i = 0;
	new_limiter = calloc(1, 1);
	if (!new_limiter)
		return (NULL);
	*quote = false;
	if (limiter[0] == '\'' || limiter[0] == '"')
		*quote = true;
	if (limiter[ft_strlen(limiter) - 1] == '\''
		|| limiter[ft_strlen(limiter) - 1] == '"')
		*quote = true;
	while (limiter[i])
	{
		if (limiter[i] != '\'' && limiter[i] != '"')
		{
			new_limiter = realloc(new_limiter, i + 1);
			if (!new_limiter)
			{
				free(new_limiter);
				return (NULL);
			}
			new_limiter[ft_strlen(new_limiter)] = limiter[i];
		}
		i++;
	}
	new_limiter[ft_strlen(new_limiter)] = '\0';
	free(limiter);
	return (new_limiter);
}

int	ft_heredoc(char *limiter, char **env)
{
	int		fd;
	char	*filename;
	char	*line;
	t_bool	quote;

	filename = ft_get_temp_filename();
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell");
		return (-1);
	}
	limiter = get_right_limiter(limiter, &quote);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, limiter) || g_exit)
		{
			free(line);
			break ;
		}
		if (!quote)
			line = ft_get_bash_string(line, env);
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
