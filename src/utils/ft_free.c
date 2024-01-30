/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:59:48 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/30 06:44:55 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_str_lst	*ft_free_str_lst(t_str_lst *lst)
{
	t_str_lst	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->value);
		free(lst);
		lst = tmp;
	}
	lst = NULL;
	return (lst);
}

t_stdin_lst	*ft_free_stdin_lst(t_stdin_lst *lst)
{
	t_stdin_lst	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->value);
		free(lst);
		lst = tmp;
	}
	lst = NULL;
	return (lst);
}

t_out	*ft_free_out_lst(t_out *lst)
{
	t_out	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->to);
		free(lst);
		lst = tmp;
	}
	lst = NULL;
	return (lst);
}

char	**ft_free_char_array(char **array)
{
	int	i;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	array = NULL;
	return (array);
}

void	free_all(t_subshell *subshell, int mode)
{
	while (subshell)
	{
		if (subshell->argv)
			subshell->argv = ft_free_str_lst(subshell->argv);
		if (subshell->stdin)
			subshell->stdin = ft_free_stdin_lst(subshell->stdin);
		if (subshell->outfiles)
			subshell->outfiles = ft_free_out_lst(subshell->outfiles);
		if (subshell->env && mode == 1)
			subshell->env = ft_free_char_array(subshell->env);
		if (subshell->cmds)
		{
			free_all(subshell->cmds, 1);
			subshell->cmds = NULL;
		}
		subshell = subshell->next;
	}
}
