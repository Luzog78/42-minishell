/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:59:48 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/23 20:11:47 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	ft_free_str_lst(t_str_lst *lst)
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
}

void	ft_free_stdin_lst(t_stdin_lst *lst)
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
}

void	ft_free_out_lst(t_out *lst)
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
}

void	ft_free_char_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	array = NULL;
}

void	free_all(t_subshell *subshell, int mode)
{
	while (subshell)
	{
		if (subshell->argv)
			ft_free_str_lst(subshell->argv);
		if (subshell->stdin)
			ft_free_stdin_lst(subshell->stdin);
		if (subshell->outfiles)
			ft_free_out_lst(subshell->outfiles);
		if (subshell->env && mode == 1)
			ft_free_char_array(subshell->env);
		if (subshell->type == SUBSHELL)
			free_all(subshell->cmds, 1);
		subshell = subshell->next;
	}
}
