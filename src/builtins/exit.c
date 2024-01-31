/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:00:04 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/31 12:43:48 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_isdigit(char *str)
{
	int			i;
	long long	result;

	i = 0;
	result = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '-')
			return (0);
		result = (result * 10) + (str[i] - '0');
		if (result == 922337203685477580 && str[i + 1] >= '8' && str[i + 1] <= '9')
			return (0);
		else if(result == -922337203685477580 && str[i + 1] <= '9')
			return (0);
		else if (result > 922337203685477580 && str[i + 1])
			return (0);
		else if (result < -922337203685477580 && str[i + 1])
			return (0);
		i++;
	}
	return (1);
}

long long	ft_atoi(char *number)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (number[i] == ' ' || number[i] == '\t' || number[i] == '\n'
		|| number[i] == '\v' || number[i] == '\f' || number[i] == '\r')
		i++;
	if (number[i] == '-')
		sign = -1;
	if (number[i] == '-' || number[i] == '+')
		i++;
	while (number[i] >= '0' && number[i] <= '9')
	{
		if (result > 9223372036854775807 && sign == 1)
			return (-1);
		result = result * 10 + number[i] - '0';
		i++;
	}
	return (result * sign);
}

int	ft_exit(char **argv)
{
	int	exit_code;

	exit_code = 0;
	if (argv[1])
	{

		if (argv[1][0] != '-' && ft_isdigit(argv[1]) && !argv[2])
			exit_code = ft_atoi(argv[1]) % 256;
		else if (argv[1][0] == '-' && ft_isdigit(argv[1]) && !argv[2])
			exit_code = 256 + (ft_atoi(argv[1]) % 256);
		else if (argv[1] && !ft_isdigit(argv[1]))
			exit_code = 2;
		else if (argv[1] && argv[2])
			return (1);
	}
	printf("exit %d\n", exit_code);
	exit(exit_code);
	return (0);
}
