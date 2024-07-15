/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:22:28 by sdell-er          #+#    #+#             */
/*   Updated: 2024/07/15 19:19:59 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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

void	*check_death(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	sem_wait(philo->is_dead);
	sem_post(philo->is_dead);
	sem_wait(philo->dead_sem);
	philo->dead = philo->i;
	sem_post(philo->dead_sem);
	return (NULL);
}

void	*check_starvation(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	while (1)
	{
		sem_wait(philo->dead_sem);
		if (philo->dead)
		{
			sem_post(philo->dead_sem);
			return (NULL);
		}
		sem_post(philo->dead_sem);
		sem_wait(philo->eaten_sem);
		if (philo->nb_eat != -1 && philo->eaten)
		{
			sem_post(philo->eaten_sem);
			return (NULL);
		}
		sem_post(philo->eaten_sem);
		sem_wait(philo->last_meal_sem);
		if (get_time(philo->tv) - philo->last_meal > philo->time_to_die / 1000)
		{
			sem_post(philo->last_meal_sem);
			sem_wait(philo->dead_sem);
			if (philo->dead)
			{
				sem_post(philo->dead_sem);
				return (NULL);
			}
			philo->dead = philo->i;
			sem_wait(philo->print);
			printf("%ld %d %s\n", get_time(philo->tv), philo->i, DIE);
			sem_post(philo->print);
			sem_post(philo->dead_sem);
			sem_post(philo->is_dead);
			return (NULL);
		}
		sem_post(philo->last_meal_sem);
		usleep(1000);
	}
	return (NULL);
}
