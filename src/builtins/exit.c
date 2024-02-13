/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:00:04 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/13 05:14:36 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	ft_isdigit(char *str)
{
	int			i;
	long long	result;

	i = 0;
	result = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '-' && str[i] != '+')
			return (0);
		result = (result * 10) + (str[i] - '0');
		if (result == 922337203685477580 && str[i + 1] >= '8'
			&& str[i + 1] <= '9')
			return (0);
		else if (result == -922337203685477580 && str[i + 1] <= '9')
			return (0);
		else if (result > 922337203685477580 && str[i + 1])
			return (0);
		else if (result < -922337203685477580 && str[i + 1])
			return (0);
		i++;
	}
	return (1);
}

static long long	ft_atoi(char *number)
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

static int	get_exit_code(char **argv, t_subshell *cmds)
{
	int	exit_code;

	exit_code = 0;
	if (argv[1][0] != '-' && ft_isdigit(argv[1]) && !argv[2])
		exit_code = ft_atoi(argv[1]) % 256;
	else if (argv[1][0] == '-' && ft_isdigit(argv[1]) && !argv[2])
		exit_code = 256 + (ft_atoi(argv[1]) % 256);
	else if (argv[1] && !ft_isdigit(argv[1]))
	{
		ft_printf_err("exit: p: numeric argument required ('%s')\n", argv[1]);
		ft_free_cmds(ft_get_parent(cmds));
		ft_free_char_array(argv);
		exit(2);
	}
	return (exit_code);
}

int	ft_exit(t_subshell *cmds, char **argv)
{
	int	exit_code;

	exit_code = 0;
	if (argv[1])
	{
		exit_code = get_exit_code(argv, cmds);
		if (argv[1] && argv[2])
		{
			ft_print_err("exit: too many arguments\n");
			return (1);
		}
	}
	printf("exit\n");
	ft_free_char_array(argv);
	ft_free_cmds(ft_get_parent(cmds));
	exit(exit_code);
	return (0);
}
