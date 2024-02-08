/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 03:02:38 by ysabik            #+#    #+#             */
/*   Updated: 2024/02/08 03:14:20 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

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

void	ft_printf_err2(char *str, char *err1, char *err2)
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
			if (err1)
			{
				write(2, err1, ft_strlen(err1));
				err1 = NULL;
			}
			else
				write(2, err2, ft_strlen(err2));
			i += 2;
		}
		write(2, &str[i], 1);
		i++;
	}
}
