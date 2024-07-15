/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_starvation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:23:38 by sdell-er          #+#    #+#             */
/*   Updated: 2024/07/15 14:23:39 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	insufficient_time(t_philo *philo, int last_meal, int i1, int i2)
{
	return (philo->started_eating[i1] + philo->time_to_eat / 1000
		> last_meal + philo->time_to_die / 1000 + 5
		|| philo->started_eating[i2] + philo->time_to_eat / 1000
		> last_meal + philo->time_to_die / 1000 + 5);
}

static int	check_starvation_two(t_philo *philo, int i, int last_meal)
{
	pthread_mutex_lock(&(philo->started_eating_mutex[i % 2]));
	if (philo->started_eating[i % 2] + philo->time_to_eat / 1000
		> last_meal + philo->time_to_die / 1000 + 5)
	{
		pthread_mutex_unlock(&(philo->started_eating_mutex[i % 2]));
		usleep(philo->time_to_die - (get_time(philo->tv) - last_meal) * 1000);
		pthread_mutex_lock(&(philo->mutex));
		if (philo->dead)
		{
			pthread_mutex_unlock(&(philo->mutex));
			return (1);
		}
		philo->dead = i;
		pthread_mutex_unlock(&(philo->mutex));
		print(philo, i, DIE);
		return (1);
	}
	pthread_mutex_unlock(&(philo->started_eating_mutex[i % 2]));
	return (0);
}

int	check_starvation(t_philo *philo, int i, int last_meal)
{
	int	i1;
	int	i2;

	if (philo->nb_philo == 2)
		return (check_starvation_two(philo, i, last_meal));
	i1 = get_i_started_eating(philo->nb_philo, i, 1);
	i2 = get_i_started_eating(philo->nb_philo, i, 2);
	pthread_mutex_lock(&(philo->started_eating_mutex[i1]));
	pthread_mutex_lock(&(philo->started_eating_mutex[i2]));
	if (insufficient_time(philo, last_meal, i1, i2))
	{
		pthread_mutex_unlock(&(philo->started_eating_mutex[i2]));
		pthread_mutex_unlock(&(philo->started_eating_mutex[i1]));
		usleep(philo->time_to_die - (get_time(philo->tv) - last_meal) * 1000);
		pthread_mutex_lock(&(philo->mutex));
		if (philo->dead)
			return (unlock_mutex(philo, i, 0));
		philo->dead = i;
		pthread_mutex_unlock(&(philo->mutex));
		print(philo, i, DIE);
		return (1);
	}
	pthread_mutex_unlock(&(philo->started_eating_mutex[i2]));
	pthread_mutex_unlock(&(philo->started_eating_mutex[i1]));
	return (0);
}
