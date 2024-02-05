/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:23:31 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/05 14:55:49 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

char	*get_next_line(int fd, char *limiter)
{
	char	*line;
	char	*tmp;
	int		ret;

	tmp = malloc(2);
	tmp[1] = '\0';
	line = malloc(1);
	if (!line)
		return (NULL);
	while (!ft_strchr(line, '\n'))
	{
		ret = read(fd, tmp, 1);
		if (ret == 0)
			break ;
		line = ft_strjoin(line, tmp);
		if (ft_strcmp(line, limiter) == 0)
			break ;
	}
	free(tmp);
	return (line);
}
