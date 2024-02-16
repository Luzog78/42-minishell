/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:15:30 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/16 15:19:24 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtins.h"

int	ft_dup_infiles(char *infile, char **env)
{
	int		fd;
	char	*path;

	path = ft_get_bash_string(infile, env, FALSE);
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
		path = ft_get_bash_string(outfiles->to, env, FALSE);
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
