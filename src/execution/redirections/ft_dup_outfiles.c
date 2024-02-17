/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_outfiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 02:46:46 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 04:56:28 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
			g_exit = 1;
			return (g_exit);
		}
		dup2(fd, outfiles->from);
		close(fd);
		free(path);
		outfiles = outfiles->next;
	}
	return (0);
}
