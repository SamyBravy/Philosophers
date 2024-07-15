/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:23:33 by sdell-er          #+#    #+#             */
/*   Updated: 2024/07/15 14:23:34 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

static void	init(t_philo *philo, pthread_t **p_threads, int argc, char **argv)
{
	philo->nb_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]) * 1000;
	philo->time_to_eat = ft_atoi(argv[3]) * 1000;
	philo->time_to_sleep = ft_atoi(argv[4]) * 1000;
	philo->nb_eat = -1;
	if (argc == 6)
		philo->nb_eat = ft_atoi(argv[5]);
	*p_threads = malloc(sizeof(pthread_t) * philo->nb_philo);
	pthread_mutex_init(&(philo->mutex), NULL);
	pthread_mutex_init(&(philo->print), NULL);
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->nb_philo);
	philo->i = 0;
	while (philo->i < philo->nb_philo)
		pthread_mutex_init(&(philo->forks[philo->i++]), NULL);
	philo->dead = 0;
	philo->started_eating = malloc(sizeof(int) * philo->nb_philo);
	memset(philo->started_eating, -9 * philo->time_to_eat,
		sizeof(int) * philo->nb_philo);
	philo->started_eating_mutex = malloc(philo->nb_philo
			* sizeof(pthread_mutex_t));
	philo->i = 0;
	while (philo->i < philo->nb_philo)
		pthread_mutex_init(&(philo->started_eating_mutex[philo->i++]), NULL);
	philo->i = 1;
}

static void	destroy(t_philo *philo, pthread_t **philo_threads)
{
	int	i;

	pthread_mutex_destroy(&(philo->mutex));
	pthread_mutex_destroy(&(philo->print));
	i = -1;
	while (++i < philo->nb_philo)
		pthread_mutex_destroy(&(philo->forks[i]));
	i = -1;
	while (++i < philo->nb_philo)
		pthread_mutex_destroy(&(philo->started_eating_mutex[i]));
	free(philo->started_eating_mutex);
	free(philo->started_eating);
	free(philo->forks);
	free(*philo_threads);
}

int	main(int argc, char **argv)
{
	t_philo		philo;
	pthread_t	*philo_threads;
	int			i;

	if (parsing(argc, argv))
		return (1);
	init(&philo, &philo_threads, argc, argv);
	i = 0;
	gettimeofday(&(philo.tv), NULL);
	while (i < philo.nb_philo)
		pthread_create(&(philo_threads[i++]), NULL, philosopher, &philo);
	i = -1;
	while (++i < philo.nb_philo)
		pthread_join(philo_threads[i], NULL);
	destroy(&philo, &philo_threads);
	return (0);
}
