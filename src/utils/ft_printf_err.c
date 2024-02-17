/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 03:02:38 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/17 04:46:48 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_perror(void)
{
	perror("minishell");
	g_exit = 1;
}

int	ft_perror_ret(void)
{
	ft_perror();
	return (g_exit);
}

void	ft_print_err(char *str)
{
	write(2, str, ft_strlen(str));
}

void	ft_printf_err(char *str, char *err)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] == '%')
		{
			write(2, &str[i], 1);
			i += 2;
		}
		if (str[i] == '%' && str[i + 1] == 's')
		{
			write(2, err, ft_strlen(err));
			i += 2;
		}
		write(2, &str[i], 1);
		i++;
	}
}
