/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 00:48:14 by marvin            #+#    #+#             */
/*   Updated: 2024/07/15 00:48:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' || str[i] == '-')
		{
			if (!(str[i + 1] >= '0' && str[i + 1] <= '9') || i)
				return (0);
		}
		else if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

static int	all_numbers(char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_digit(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	parsing(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (printf("Error: Wrong number of arguments\n"));
	if (!all_numbers(argv, argc))
		return (printf("Error: Arguments must be numbers\n"));
	if (ft_atoi(argv[1]) < 1)
		return (printf("Error: Number of philosophers must be at least 1\n"));
	if (ft_atoi(argv[2]) < 1)
		return (printf("Error: Time to die must be at least 1\n"));
	if (ft_atoi(argv[3]) < 1)
		return (printf("Error: Time to eat must be at least 1\n"));
	if (ft_atoi(argv[4]) < 1)
		return (printf("Error: Time to sleep must be at least 1\n"));
	if (argc == 6 && ft_atoi(argv[5]) < 1)
		return (printf("Error: Philosophers must eat at least 1 time\n"));
	return (0);
}
