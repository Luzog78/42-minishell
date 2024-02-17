/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_wildcard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 02:36:02 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 02:36:17 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_append_wildcard(char ***args, char *str, char **env)
{
	DIR			*dir;
	char		*new;
	t_bool		is_matched;
	char		*tmp;
	t_str_lst	*tmp_args;

	new = ft_get_bash_string(str, env, TRUE);
	tmp_args = NULL;
	is_matched = FALSE;
	dir = opendir(".");
	if (!dir)
	{
		free(new);
		free(str);
		return ;
	}
	while (1)
	{
		struct dirent	*entry;
		entry = readdir(dir);
		if (!entry)
			break ;
		if ((entry->d_name[0] != '.' || new[0] == '.')
			&& wc_allow(entry->d_name, new))
		{
			is_matched = TRUE;
			tmp = ft_strdup(entry->d_name);
			if (tmp)
				ft_str_lst_add(&tmp_args, tmp);
		}
	}
	if (!is_matched)
	{
		free(new);
		new = ft_get_bash_string(str, env, FALSE);
		if (new)
			ft_args_realloc(args, new);
	}
	else
	{
		ft_sort_list(&tmp_args);
		ft_args_reallocs(args, &tmp_args);
	}
	free(new);
	free(str);
	closedir(dir);
}
