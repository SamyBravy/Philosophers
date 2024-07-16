/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_ft_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:28:44 by sdell-er          #+#    #+#             */
/*   Updated: 2024/07/16 17:32:31 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*check_death(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	sem_wait(philo->is_dead);
	sem_post(philo->is_dead);
	sem_wait(philo->dead_sem);
	if (!philo->dead)
		philo->dead = -42;
	sem_post(philo->dead_sem);
	return (NULL);
}

static void	*set_death(t_philo *philo)
{
	sem_post(philo->last_meal_sem);
	sem_wait(philo->print);
	sem_wait(philo->dead_sem);
	if (philo->dead)
	{
		sem_post(philo->dead_sem);
		sem_post(philo->print);
		return (NULL);
	}
	philo->dead = philo->i;
	sem_post(philo->dead_sem);
	sem_post(philo->is_dead);
	printf("%ld %d %s\n", get_time(philo->tv), philo->i, DIE);
	philo->j = 0;
	while (philo->j < philo->nb_philo)
		sem_post(philo->finished_eating[philo->j++]);
	return (NULL);
}

void	*check_starvation(void *philosopher)
{
	while (1)
	{
		sem_wait(((t_philo *)philosopher)->dead_sem);
		if (((t_philo *)philosopher)->dead)
		{
			sem_post(((t_philo *)philosopher)->dead_sem);
			return (NULL);
		}
		sem_post(((t_philo *)philosopher)->dead_sem);
		sem_wait(((t_philo *)philosopher)->eaten_sem);
		if (((t_philo *)philosopher)->nb_eat != -1
			&& ((t_philo *)philosopher)->eaten)
		{
			sem_post(((t_philo *)philosopher)->eaten_sem);
			return (NULL);
		}
		sem_post(((t_philo *)philosopher)->eaten_sem);
		sem_wait(((t_philo *)philosopher)->last_meal_sem);
		if (get_time(((t_philo *)philosopher)->tv)
			- ((t_philo *)philosopher)->last_meal
			> ((t_philo *)philosopher)->time_to_die / 1000 + 5)
			return (set_death(((t_philo *)philosopher)));
		usleep(1000 + 0 * sem_post(((t_philo *)philosopher)->last_meal_sem));
	}
	return (NULL);
}
