/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:05:30 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/08 02:00:28 by ysabik           ###   ########.fr       */
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
	new = calloc(sizeof(char *), (i + 2));
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

void	ft_append_wildkartttt(char ***args, char *str, char **env)
{
	char	quote;
	char	*tmp;
	DIR		*dir;
	
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
	if (quote)
	{
		tmp = ft_get_bash_string(str, env);
		free(str);
		if (!tmp)
			return ;
		ft_realloc(args, tmp);
		return ;
	}
	free(str);
	
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
		if (entry->d_name[0] != '.')
		{
			tmp = ft_strdup(entry->d_name);
			if (tmp)
				ft_realloc(args, tmp);
		}
	}
	closedir(dir);
}

void ft_append_str(char ***args, char *str, char **env)
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
	if (str[0] != '*' || str[1] != '\0')
	{
		free(str);
		ft_realloc(args, new);
		return ;
	}
	free(new);
	ft_append_wildkartttt(args, str, env);
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
