/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:23:20 by sdell-er          #+#    #+#             */
/*   Updated: 2024/07/15 14:23:21 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	get_time(struct timeval tv)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec - tv.tv_sec) * 1000
		+ (current.tv_usec - tv.tv_usec) / 1000);
}

int	get_i_fork(int nb_philo, int i, int k)
{
	if (i == nb_philo && k == 1)
		return (0);
	if (i == nb_philo && k == 2)
		return (nb_philo - 1);
	if (k == 1)
		return (i - 1);
	else
		return (i);
}

int	get_i_started_eating(int nb_philo, int i, int k)
{
	if (i == nb_philo && k == 1)
		return (0);
	if (i == nb_philo && k == 2)
		return (nb_philo - 1);
	if (i == 1 && k == 1)
		return (1);
	if (i == 1 && k == 2)
		return (nb_philo - 1);
	if (k == 1)
		return (i - 2);
	else
		return (i % nb_philo);
}

int	print(t_philo *philo, int i, char *str)
{
	pthread_mutex_lock(&(philo->mutex));
	if (philo->dead && philo->dead != i)
	{
		pthread_mutex_unlock(&(philo->mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->mutex));
	pthread_mutex_lock(&(philo->print));
	printf("%ld %d %s\n", get_time(philo->tv), i, str);
	pthread_mutex_unlock(&(philo->print));
	return (0);
}

int	unlock_mutex(t_philo *philo, int i, int k)
{
	if (k == 0)
		pthread_mutex_unlock(&(philo->mutex));
	else if (k == 1)
		pthread_mutex_unlock(&(philo->forks
			[get_i_fork(philo->nb_philo, i, 1)]));
	else if (k == 2)
	{
		pthread_mutex_unlock(&(philo->forks
			[get_i_fork(philo->nb_philo, i, 2)]));
		pthread_mutex_unlock(&(philo->forks
			[get_i_fork(philo->nb_philo, i, 1)]));
	}
	else if (k == 3)
	{
		pthread_mutex_unlock(&(philo->forks
			[get_i_fork(philo->nb_philo, i, 2)]));
		pthread_mutex_unlock(&(philo->forks
			[get_i_fork(philo->nb_philo, i, 1)]));
		pthread_mutex_unlock(&(philo->mutex));
	}
	return (1);
}
