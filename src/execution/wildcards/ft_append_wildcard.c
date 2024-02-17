/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_wildcard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 02:36:02 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 03:42:07 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_bool	ft_readdir(DIR *dir, char *new, t_str_lst **tmp_args)
{
	struct dirent	*entry;
	t_bool			matched;
	char			*tmp;

	matched = FALSE;
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if ((entry->d_name[0] != '.' || new[0] == '.')
			&& wc_allow(entry->d_name, new))
		{
			matched = TRUE;
			tmp = ft_strdup(entry->d_name);
			if (tmp)
				ft_str_lst_add(tmp_args, tmp);
		}
	}
	return (matched);
}

void	ft_append_wildcard(char ***args, char *str, char **env)
{
	DIR			*dir;
	char		*new;
	t_str_lst	*tmp_args;

	new = ft_get_bash_string(str, env, TRUE);
	tmp_args = NULL;
	dir = opendir(".");
	if (dir && !ft_readdir(dir, new, &tmp_args))
	{
		free(new);
		new = ft_get_bash_string(str, env, FALSE);
		if (new)
			ft_args_realloc(args, new);
	}
	else if (dir)
	{
		ft_sort_list(&tmp_args);
		ft_args_reallocs(args, &tmp_args);
	}
	free(new);
	free(str);
	closedir(dir);
}
