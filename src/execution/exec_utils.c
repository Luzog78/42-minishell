/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:05:30 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/17 01:46:08 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	allow_next(t_subshell *cmds)
{
	if (cmds->link == PIPE || cmds->link == PIPE_AND)
		return (1);
	if (cmds->link == AND && g_exit == 0)
		return (1);
	if (cmds->link == OR && g_exit != 0)
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

void	ft_reallocs(char ***args, t_str_lst **lst)
{
	t_str_lst	*cursor;
	t_str_lst	*tmp;

	cursor = *lst;
	while (cursor)
	{
		ft_realloc(args, cursor->value);
		free(cursor->value);
		tmp = cursor->next;
		free(cursor);
		cursor = tmp;
	}
	*lst = NULL;
}

char	*ft_tolower(const char *str)
{
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if ((str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= '0' && str[i] <= '9'))
			j++;
	}
	new = ft_calloc(sizeof(char), j + 1);
	if (!new)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			new[j++] = str[i] + 32;
		else if ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= '0' && str[i] <= '9'))
			new[j++] = str[i];
	}
	return (new);
}

int	ft_strcmp_ignore_case(const char *s1, const char *s2)
{
	const char	*str1;
	const char	*str2;
	size_t		i;
	int			result;

	result = 0;
	str1 = ft_tolower(s1);
	str2 = ft_tolower(s2);
	if (str1 && str2)
	{
		i = 0;
		while (str1[i] && str2[i] && str1[i] == str2[i])
			i++;
		result = (unsigned char)str1[i] - (unsigned char)str2[i];
	}
	free((char *)str1);
	free((char *)str2);
	return (result);
}

void	ft_sort_list(t_str_lst **lst)
{
	t_str_lst	*cursor;
	t_str_lst	*tmp;
	char		*tmp_str;

	cursor = *lst;
	while (cursor)
	{
		tmp = cursor->next;
		while (tmp)
		{
			if (ft_strcmp_ignore_case(cursor->value, tmp->value) > 0)
			{
				tmp_str = cursor->value;
				cursor->value = tmp->value;
				tmp->value = tmp_str;
			}
			tmp = tmp->next;
		}
		cursor = cursor->next;
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
	DIR			*dir;
	char		*new;
	t_bool		is_matched;
	char		*tmp;
	t_str_lst	*tmp_args;

	// tmp = ft_get_bash_string(str, env, TRUE);
	// if (tmp && is_star_between_quote(tmp))
	// {
	// 	free(tmp);
	// 	tmp = ft_get_bash_string(str, env, FALSE);
	// 	free(str);
	// 	if (!tmp)
	// 		return ;
	// 	ft_realloc(args, tmp);
	// 	free(tmp);
	// 	return ;
	// }
	// free(tmp);
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
		// printf("entry->d_name: %s\n", entry->d_name);
		if ((entry->d_name[0] != '.' || new[0] == '.') && ft_wildcard_allow(entry->d_name, new))
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
			ft_realloc(args, new);
	}
	else
	{
		ft_sort_list(&tmp_args);
		ft_reallocs(args, &tmp_args);
	}
	free(new);
	free(str);
	closedir(dir);
}

void	ft_append_str(char ***args, char *str, char **env)
{
	char	*new;

	if (!str)
		return ;
	new = ft_get_bash_string(str, env, TRUE);
	if (!new)
	{
		free(str);
		return ;
	}
	if (!ft_is_wildcard(new))
	{
		free(new);
		new = ft_get_bash_string(str, env, FALSE);
		free(str);
		if (new)
			ft_realloc(args, new);
		free(new);
		return ;
	}
	free(new);
	ft_append_wildkartttt(args, str, env);
}

int	get_last_elem(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
		i++;
	return (i - 1);
}

char	**ft_lststr_to_char_array(t_str_lst *lst, char **env)
{
	char		**array;
	char		**tmp_array;
	int			i;
	int			j;

	array = NULL;
	i = 0;
	while (lst)
	{
		j = 0;
		ft_append_str(&array, ft_strdup(lst->value), env);
		if (lst->value[0] == '$')
		{
			if (!array || !array[i])
			{
				lst = lst->next;
				continue ;
			}
			tmp_array = NULL;
			tmp_array = ft_split(array[i], ' ');
			if (strcmp(tmp_array[0], array[i]) == 0)
			{
				ft_free_char_array(tmp_array);
				lst = lst->next;
				continue ;
			}
			free(array[i]);
			array[i] = NULL;
			while (tmp_array && tmp_array[j])
			{
				ft_append_str(&array, ft_strdup(tmp_array[j]), env);
				free(tmp_array[j]);
				j++;
				if (tmp_array[j])
					i++;
			}
			free(tmp_array);
		}
		i++;
		lst = lst->next;
	}
	return (array);
}
