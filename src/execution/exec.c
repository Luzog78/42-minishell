/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 22:46:42 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/16 03:38:33 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int	ft_dup_infile(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
		return (1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	ft_dup_outfiles(t_out *outfiles)
{
	int	fd;

	fd = -1;
	if (outfiles->type == REPLACE)
		fd = open(outfiles->to, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (outfiles->type == APPEND)
		fd = open(outfiles->to, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (1);
	dup2(fd, outfiles->from);
	close(fd);
	return (0);
}

char	*ft_get_temp_filename(void)
{
	//FAIRE UN truc AVEC UN ACCESS(FILENAME, F_OK) POUR VERIFIER SI LE FICHIER EXISTE
	return (ft_strdup(".temp"));
}

int	ft_heredoc(char *limiter)
{
	char	*line;
	char	*temp_filename;
	int		temp_fd;

	line = NULL;
	temp_filename = ft_get_temp_filename();
	temp_fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp_fd == -1)
		return (1);
	while (ft_strcmp(line, limiter))
	{
		line = readline("> ");
		write(temp_fd, line, ft_strlen(line));
	}
	dup2(temp_fd, STDIN_FILENO);
	unlink(temp_filename);
	free(temp_filename);
	close(temp_fd);
	return (0);
}

void	ft_exec_cmd(t_subshell *cmds)
{
	if (!cmds->exit_status && cmds->heredoc_limiter)
		cmds->exit_status = ft_heredoc(cmds->heredoc_limiter);
	if (!cmds->exit_status && cmds->infile)
		cmds->exit_status = ft_dup_infile(cmds->infile);
	if (!cmds->exit_status && cmds->outfiles)
		cmds->exit_status = ft_dup_outfiles(cmds->outfiles);
	if (!cmds->next)
		return ;
	if (cmds->next->type == COMMAND)
		ft_exec_cmd(cmds->next);
	else if (cmds->next->type == SUBSHELL)
		ft_exec_subshell(cmds->next);
}

void	ft_exec_subshell(t_subshell *subshell)
{
	if (!subshell)
		return ;
	if (subshell->next->type == COMMAND)
		ft_exec_cmd(subshell->next);
	else if (subshell->next->type == SUBSHELL)
		ft_exec_subshell(subshell->next);
}

void	ft_exec(t_subshell *subshell)
{
	ft_exec_cmd(subshell->cmds);
	ft_subshell_init(subshell, SUBSHELL, subshell->env);
}
