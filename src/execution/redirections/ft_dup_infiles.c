/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_infiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 02:46:29 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 02:46:37 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
