/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:05:30 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/11 03:05:22 by bcarolle         ###   ########.fr       */
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

int	get_index(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '*')
		i++;
	return (i);
}

static t_bool	ft_wildcard_allow(char *file, char *str)
{
	char	*tmpfile;
	char	*tmpwild;
	t_bool	ret;

	ret = FALSE;
	tmpfile = file;
	tmpwild = str;
	while (*tmpfile && *tmpwild)
	{
		if (*tmpwild == '*')
		{
			tmpwild++;
			if (!*tmpwild)
				return (TRUE);
			while (*tmpfile &&
				ft_strcmp(
					ft_substr(tmpfile, 0, get_index(tmpwild)),
					ft_substr(tmpwild, 0, get_index(tmpwild))) != 0)
				tmpfile++;
 			if (!*tmpfile)
				return (FALSE);
			ret = TRUE;
		}
		else if (*tmpfile != *tmpwild)
			return (FALSE);
		tmpfile++;
		tmpwild++;
	}
	if (!*tmpfile && (!*tmpwild || *tmpwild == '*'))
		return (ret);
	return (FALSE);
}

void	ft_append_wildkartttt(char ***args, char *str, char **env)
{
	char	quote;
	char	*tmp;
	DIR		*dir;
	char	*new;
	t_bool	is_matched;

	quote = 0;
	tmp = str;
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
	if (quote) //return error cuz its way too complex to handle
	{
		// tmp = ft_get_bash_string(str, env);
		// free(str);
		// if (!tmp)
		// 	return ;
		// ft_realloc(args, tmp);
		write(2, "minishell: wildcard not allowed in quotes\n", 42);
		return ;
	}
	new = ft_get_bash_string(str, env);
	free(str);
	is_matched = FALSE;
	// There is a wild card. So we need to find all the files that is IN THE CURRENT DIRECTORY
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
				ft_realloc(args, tmp);
		}
	}
	if (!is_matched)
		ft_realloc(args, new);
	closedir(dir);
}

t_bool	ft_is_wildcard(char *str)
{
	while (*str)
	{
		if (*str == '*')
			return (TRUE);
		str++;
	}
	return (FALSE);
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
