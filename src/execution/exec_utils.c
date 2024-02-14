/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:05:30 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/14 04:51:06 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	allow_next(t_subshell *cmds)
{
	if (cmds->link == PIPE || cmds->link == PIPE_AND)
		return (1);
	if (cmds->link == AND && cmds->exit_status == 0)
		return (1);
	if (cmds->link == OR && cmds->exit_status != 0)
		return (1);
	return (0);
}

size_t	ft_lstsize(t_str_lst *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

static void	ft_realloc(char ***args, char *str)
{
	char	**new;
	int		i;

	i = 0;
	while (*args && (*args)[i])
		i++;
	new = ft_calloc(sizeof(char *), (i + 2));
	if (!new)
		return ;
	i = 0;
	while (*args && (*args)[i])
	{
		new[i] = ft_strdup((*args)[i]);
		i++;
	}
	new[i] = ft_strdup(str);
	i = 0;
	while (*args && (*args)[i])
	{
		free((*args)[i]);
		i++;
	}
	free(*args);
	*args = new;
}

void	ft_sort_args(char ***args)
{
	int		i;
	int		j;
	char	*tmp;

	i = 1;
	while (*args && (*args)[i])
	{
		j = i + 1;
		while (*args && (*args)[j])
		{
			if (ft_strcmp((*args)[i], (*args)[j]) > 0)
			{
				tmp = (*args)[i];
				(*args)[i] = (*args)[j];
				(*args)[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

t_bool	is_star_between_quote(char *tmp)
{
	char	quote;

	quote = 0;
	while (*tmp && *tmp != '*')
	{
		if (*tmp == '\'' || *tmp == '"')
		{
			if (!quote)
				quote = *tmp;
			else if (quote == *tmp)
				quote = 0;
		}
		tmp++;
	}
	//*e"*"

	//*e\*
	return (quote != 0);
}

void	ft_append_wildkartttt(char ***args, char *str, char **env)
{
	DIR		*dir;
	char	*new;
	t_bool	is_matched;
	char	*tmp;

	tmp = str;
	if (is_star_between_quote(tmp))
	{
		tmp = ft_get_bash_string(str, env);
		free(str);
		if (!tmp)
			return ;
		ft_realloc(args, tmp);
		free(tmp);
		return ;
	}
	new = ft_get_bash_string(str, env);
	free(str);
	is_matched = FALSE;
	dir = opendir(".");
	if (!dir)
		return ;
	while (1)
	{
		struct dirent	*entry;
		entry = readdir(dir);
		if (!entry)
			break ;
		if (entry->d_name[0] != '.' && ft_wildcard_allow(entry->d_name, new))
		{
			is_matched = TRUE;
			tmp = ft_strdup(entry->d_name);
			if (tmp)
			{
				ft_realloc(args, tmp);
				free(tmp);
			}
		}
	}
	if (!is_matched)
		ft_realloc(args, new);
	free(new);
	closedir(dir);
}

void	ft_append_str(char ***args, char *str, char **env)
{
	char	*new;

	if (!str)
		return ;
	new = ft_get_bash_string(str, env);
	if (!new)
	{
		free(str);
		return ;
	}
	if (!ft_is_wildcard(new))
	{
		free(str);
		ft_realloc(args, new);
		free(new);
		return ;
	}
	ft_append_wildkartttt(args, str, env);
	ft_sort_args(args);
	free(new);
}

char	**ft_lststr_to_char_array(t_str_lst *lst, char **env)
{
	char	**array;

	array = NULL;
	while (lst)
	{
		ft_append_str(&array, ft_strdup(lst->value), env);
		lst = lst->next;
	}
	return (array);
}
