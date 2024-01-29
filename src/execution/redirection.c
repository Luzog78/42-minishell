/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:15:30 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/29 17:46:03 by bcarolle         ###   ########.fr       */
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
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
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
	//do a function that returns a random string
	char	*random;

	random = ft_strdup("/tmp/minishell_XXXXXX");

	return (random);
}

int	ft_heredoc(char *limiter)
{
	char	*line;
	char	*temp_filename;
	int		temp_fd;

	line = NULL;
	temp_filename = ft_get_temp_filename();
	temp_fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (temp_fd == -1)
	{
		perror("minishell");
		return (1);
	}
	while (ft_strcmp(line, limiter))
	{
		line = readline("> ");
		if (ft_strcmp(line, limiter) == 0)
			break ;
		line = ft_strjoin(line, "\n");
		write(temp_fd, line, ft_strlen(line));
	}
	close(temp_fd);
	temp_fd = open(temp_filename, O_RDONLY);
	dup2(temp_fd, STDIN_FILENO);
	close(temp_fd);
	unlink(temp_filename);
	free(temp_filename);
	return (0);
}

int	ft_stdin(t_stdin_lst *stdin)
{
	int	exit_status;

	exit_status = 0;
	while (stdin)
	{
		if (stdin->type == HEREDOC)
			exit_status = ft_heredoc(stdin->value);
		else if (stdin->type == INFILE)
			exit_status = ft_dup_infiles(stdin->value);
		if (exit_status)
			return (exit_status);
		stdin = stdin->next;
	}
	return (0);
}
