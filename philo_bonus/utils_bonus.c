/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:22:28 by sdell-er          #+#    #+#             */
/*   Updated: 2024/07/16 17:28:35 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	n;
	int	res;

	n = 0;
	i = 1;
	res = 0;
	while ((nptr[n] >= 9 && nptr[n] <= 13) || nptr[n] == ' ')
		n += 1;
	if (nptr[n] == '-' || nptr[n] == '+')
	{
		if (nptr[n] == '-')
			i *= -1;
		n += 1;
	}
	while (nptr[n] >= '0' && nptr[n] <= '9')
		res = res * 10 + (nptr[n++] - '0');
	return (res * i);
}

long int	get_time(struct timeval tv)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec - tv.tv_sec) * 1000
		+ (current.tv_usec - tv.tv_usec) / 1000);
}

int	print(t_philo *philo, char *str)
{
	sem_wait(philo->dead_sem);
	if (philo->dead)
		return (42 + sem_post(philo->dead_sem));
	sem_post(philo->dead_sem);
	sem_wait(philo->print);
	printf("%ld %d %s\n", get_time(philo->tv), philo->i, str);
	sem_post(philo->print);
	return (0);
}

void	wait_finished_eating(t_philo *philo)
{
	philo->j = 0;
	while (philo->j < philo->nb_philo)
	{
		sem_wait(philo->finished_eating[philo->j]);
		sem_post(philo->finished_eating[philo->j++]);
	}
}
