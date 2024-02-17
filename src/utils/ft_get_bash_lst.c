/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_bash_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 07:57:53 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 08:21:50 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	ft_ralloc(char **str, char new)
{
	char	*tmp;
	int		i;
	size_t	size;

	if (!*str)
		size = 0;
	else
		size = ft_strlen(*str);
	tmp = ft_calloc(size + 2, sizeof(char));
	if (!tmp)
		return ;
	i = 0;
	while (*str && (*str)[i])
	{
		tmp[i] = (*str)[i];
		i++;
	}
	tmp[i] = new;
	tmp[i + 1] = '\0';
	free(*str);
	*str = tmp;
}

static t_bool	ft_bash_on_quote(char *bash_string, char **tmp,
	int *i, t_bool keep_quotes)
{
	char	quote;

	quote = bash_string[*i];
	if (keep_quotes)
		ft_ralloc(tmp, bash_string[*i]);
	while (bash_string[++(*i)] != quote && bash_string[*i] != '\0')
		ft_ralloc(tmp, bash_string[*i]);
	if (keep_quotes)
		ft_ralloc(tmp, bash_string[*i]);
	(*i)++;
	return (FALSE);
}

static void	ft_bash_add_back(t_str_lst **bash_lst, char **tmp, t_bool *empty)
{
	if (!*tmp && !*empty)
		ft_str_lst_add_back(bash_lst, ft_strdup(""));
	else if (*tmp)
		ft_str_lst_add_back(bash_lst, *tmp);
	*tmp = NULL;
	*empty = TRUE;
}

static int	ft_bash_init(t_str_lst **lst, char **tmp, t_bool *empty, int *i)
{
	*lst = NULL;
	*tmp = NULL;
	*empty = TRUE;
	*i = 0;
	return (0);
}

t_str_lst	*ft_get_bash_lst(char *str, char **env, t_bool keep_quotes)
{
	t_str_lst	*bash_lst;
	char		*bash_string;
	char		*tmp;
	t_bool		empty;
	int			i;

	ft_bash_init(&bash_lst, &tmp, &empty, &i);
	bash_string = ft_get_bash_string(str, env, TRUE);
	while (bash_string && bash_string[i])
	{
		if (bash_string[i] == '\'' || bash_string[i] == '"')
			empty = ft_bash_on_quote(bash_string, &tmp, &i, keep_quotes);
		else if (ft_is_whitespace(bash_string[i]))
		{
			ft_bash_add_back(&bash_lst, &tmp, &empty);
			while (bash_string[i] && ft_is_whitespace(bash_string[i]))
				i++;
		}
		else
			ft_ralloc(&tmp, bash_string[i++]);
	}
	ft_bash_add_back(&bash_lst, &tmp, &empty);
	free(bash_string);
	return (bash_lst);
}
