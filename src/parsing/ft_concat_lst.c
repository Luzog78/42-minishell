/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:56:46 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 10:38:41 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_concat_lst(t_str_lst *lst)
{
	char		*str;
	t_str_lst	*tmp;
	int			len;

	len = 0;
	tmp = lst;
	while (lst)
	{
		len += ft_strlen(lst->value);
		lst = lst->next;
	}
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	lst = tmp;
	while (lst)
	{
		ft_strcat(str, lst->value);
		lst = lst->next;
	}
	return (str);
}
