/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:22:37 by sdell-er          #+#    #+#             */
/*   Updated: 2024/07/15 19:22:36 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static int	get_forks(t_philo *philo, int last_meal)
{
	(void) last_meal;
	// if (check_starvation(philo, philo->i, last_meal))
	// 	return (1);
	sem_wait(philo->forks);
	if (print(philo, FORK))
		return (1);
	// if (check_starvation(philo, philo->i, last_meal))
	// 	return (42 + sem_post(philo->forks));
	sem_wait(philo->forks);
	if (print(philo, FORK))
		return (1);
	return (0);
}

static int	eat(t_philo *philo, int eaten, int *last_meal)
{
	*last_meal = get_time(philo->tv);
	sem_wait(philo->last_meal_sem);
	philo->last_meal = *last_meal;
	sem_post(philo->last_meal_sem);
	if (print(philo, EAT))
		return (1);
	if (philo->time_to_eat >= philo->time_to_die)
	{
		usleep(philo->time_to_die);
		sem_wait(philo->dead_sem);
		if (philo->dead)
			return (42 + sem_post(philo->forks) + sem_post(philo->forks)
				+ sem_post(philo->dead_sem));
		philo->dead = philo->i;
		sem_wait(philo->print);
		printf("%ld %d %s\n", get_time(philo->tv), philo->i, DIE);
		sem_post(philo->print);
		sem_post(philo->dead_sem);
		sem_post(philo->is_dead);
		sem_post(philo->forks);
		sem_post(philo->forks);
		return (1);
	}
	usleep(philo->time_to_eat);
	sem_post(philo->forks);
	sem_post(philo->forks);
	if (eaten == philo->nb_eat)
		return (1);
	return (0);
}

static int	go_to_sleep(t_philo *philo)
{
	if (print(philo, SLEEP))
		return (1);
	if (philo->time_to_sleep + philo->time_to_eat >= philo->time_to_die)
	{
		usleep(philo->time_to_die - philo->time_to_eat);
		sem_wait(philo->dead_sem);
		if (philo->dead)
			return (42 + sem_post(philo->dead_sem));
		philo->dead = philo->i;
		sem_wait(philo->print);
		printf("%ld %d %s\n", get_time(philo->tv), philo->i, DIE);
		sem_post(philo->print);
		sem_post(philo->dead_sem);
		sem_post(philo->is_dead);
		return (1);
	}
	usleep(philo->time_to_sleep);
	return (0);
}

static void	one_philo(t_philo *philo)
{
	sem_wait(philo->forks);
	print(philo, FORK);
	usleep(philo->time_to_die);
	sem_post(philo->forks);
	print(philo, DIE);
}

void	philosopher(t_philo *philo)
{
	int			eaten;
	int			last_meal;
	pthread_t	check_death_thread;
	pthread_t	check_starvation_thread;

	if (philo->nb_philo == 1)
		return (one_philo(philo));
	eaten = 0;
	if (philo->i % 2)
		usleep(400);
	pthread_create(&check_death_thread, NULL, check_death, philo);
	pthread_create(&check_starvation_thread, NULL, check_starvation, philo);
	while (philo->nb_eat == -1 || eaten++ < philo->nb_eat)
	{
		if (get_forks(philo, last_meal) || eat(philo, eaten, &last_meal)
			|| go_to_sleep(philo) || print(philo, THINK))
			break;
	}
	pthread_join(check_starvation_thread, NULL);
	pthread_join(check_death_thread, NULL);
}