/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:52:01 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/01 02:11:53 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_flags(char **argv)
{
	int		i;
	int		j;

	i = 1;
	j = 1;
	while (argv[i])
	{
		if (argv[i][0] == '-')
		{
			while (argv[i][j])
			{
				if (argv[i][j] != 'n')
					return (i);
				j++;
			}
		}
		else
			return (i);
		i++;
		j = 1;
	}
	return (i);
}

// char	*ft_getenv(char *argv, int i)
// {
// 	int		j;
// 	int		save;
// 	char	*sub_str;
// 	char	*result;

// 	save = i;
// 	j = i;
// 	while (argv[i] != ' ' && argv[i] != '\0')
// 		i++;
// 	j = i - j;
// 	sub_str = malloc(sizeof(char) * (j + 1));
// 	if (!sub_str)
// 		return (NULL);
// 	j = 0;
// 	while (argv[save] != ' ' && argv[save] != '\0')
// 	{
// 		sub_str[j] = argv[save];
// 		j++;
// 		save++;
// 	}
// 	result = getenv(sub_str);
// 	free(sub_str);
// 	return (result);
// }

void	print_string(char *argv)
{
	int		i;
	char	*var;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '$' && argv[i + 1] == '?')
		{
			printf("exitstatus");
			i++;
		}
		else if (argv[i] == '$')
		{
			var = ft_getenv(argv, i + 1);
			if (var)
			{
				printf("%s", var);
				i += ft_strlen(var) - 1;
			}
		}
		else
			printf("%c", argv[i]);
		i++;
	}
}

int	ft_echo(char **argv)
{
	// int		i;
	// int		flags;

	printf("%s\n", ft_get_bash_string(argv[1]));
	return (0);
}
