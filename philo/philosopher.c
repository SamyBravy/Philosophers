/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:25:02 by sdell-er          #+#    #+#             */
/*   Updated: 2024/07/15 17:12:24 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	get_forks(t_philo *philo, int i, int last_meal)
{
	if (check_starvation(philo, i, last_meal))
		return (1);
	pthread_mutex_lock(&(philo->forks[get_i_fork(philo->nb_philo, i, 1)]));
	if (print(philo, i, FORK))
		return (unlock_mutex(philo, i, 1));
	if (check_starvation(philo, i, last_meal))
		return (unlock_mutex(philo, i, 1));
	pthread_mutex_lock(&(philo->forks[get_i_fork(philo->nb_philo, i, 2)]));
	if (print(philo, i, FORK))
		return (unlock_mutex(philo, i, 2));
	return (0);
}

static int	eat(t_philo *philo, int i, int eaten, int *last_meal)
{
	*last_meal = get_time(philo->tv);
	pthread_mutex_lock(&(philo->started_eating_mutex[i - 1]));
	philo->started_eating[i - 1] = *last_meal;
	pthread_mutex_unlock(&(philo->started_eating_mutex[i - 1]));
	if (print(philo, i, EAT))
		return (unlock_mutex(philo, i, 2));
	if (philo->time_to_eat >= philo->time_to_die)
	{
		usleep(philo->time_to_die);
		pthread_mutex_lock(&(philo->mutex));
		if (philo->dead)
			return (unlock_mutex(philo, i, 3));
		philo->dead = i;
		pthread_mutex_unlock(&(philo->mutex));
		print(philo, i, DIE);
		return (unlock_mutex(philo, i, 2));
	}
	usleep(philo->time_to_eat);
	pthread_mutex_unlock(&(philo->forks[get_i_fork(philo->nb_philo, i, 2)]));
	pthread_mutex_unlock(&(philo->forks[get_i_fork(philo->nb_philo, i, 1)]));
	if (eaten == philo->nb_eat)
		return (1);
	return (0);
}

static int	go_to_sleep(t_philo *philo, int i)
{
	if (print(philo, i, SLEEP))
		return (1);
	if (philo->time_to_sleep + philo->time_to_eat >= philo->time_to_die)
	{
		usleep(philo->time_to_die - philo->time_to_eat);
		pthread_mutex_lock(&(philo->mutex));
		if (philo->dead)
			return (unlock_mutex(philo, i, 0));
		philo->dead = i;
		pthread_mutex_unlock(&(philo->mutex));
		print(philo, i, DIE);
		return (1);
	}
	usleep(philo->time_to_sleep);
	return (0);
}

static void	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(&(philo->forks[0]));
	print(philo, 1, FORK);
	usleep(philo->time_to_die);
	pthread_mutex_unlock(&(philo->forks[0]));
	print(philo, 1, DIE);
	return (NULL);
}

void	*philosopher(void *philosopher)
{
	int		i;
	int		eaten;
	int		last_meal;
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	if (philo->nb_philo == 1)
		return (one_philo(philo));
	pthread_mutex_lock(&(philo->mutex));
	i = philo->i++;
	pthread_mutex_unlock(&(philo->mutex));
	eaten = 0;
	last_meal = 0;
	if (i % 2)
		usleep(400);
	while (philo->nb_eat == -1 || eaten++ < philo->nb_eat)
	{
		if (get_forks(philo, i, last_meal) || eat(philo, i, eaten, &last_meal)
			|| go_to_sleep(philo, i) || print(philo, i, THINK))
			return (NULL);
	}
	return (NULL);
}
