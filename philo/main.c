/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:09:34 by samy_bravy        #+#    #+#             */
/*   Updated: 2024/07/11 14:34:14 by sdell-er         ###   ########.fr       */
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

int	init_mutexes(t_philo *philo)
{
	int	i;

	pthread_mutex_init(&(philo->mutex), NULL);
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->nb_philo);
	if (!philo->forks)
	{
		pthread_mutex_destroy(&(philo->mutex));
		return (printf("Error: malloc failed\n"));
	}
	i = 0;
	while (i < philo->nb_philo)
		pthread_mutex_init(&(philo->forks[i++]), NULL);
	return (0);
}

int	is_digit(char *str)
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

int	all_numbers(char **argv, int argc)
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

int	parsing(t_philo *philo, int argc, char **argv, pthread_t **philo_threads)
{
	if (argc != 5 && argc != 6)
		return (printf("Error: Wrong number of arguments\n"));
	if (!all_numbers(argv, argc))
		return (printf("Error: Arguments must be numbers\n"));
	philo->nb_philo = ft_atoi(argv[1]);
	if (philo->nb_philo < 1)
		return (printf("Error: Number of philosophers must be at least 1\n"));
	philo->time_to_die = ft_atoi(argv[2]);
	if (philo->time_to_die < 1)
		return (printf("Error: Time to die must be at least 1\n"));
	philo->time_to_eat = ft_atoi(argv[3]);
	if (philo->time_to_eat < 1)
		return (printf("Error: Time to eat must be at least 1\n"));
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (philo->time_to_sleep < 1)
		return (printf("Error: Time to sleep must be at least 1\n"));
	if (argc == 6)
	{
		philo->nb_eat = ft_atoi(argv[5]);
		if (philo->nb_eat < 1)
			return (printf("Error: Philosophers must eat at least 1 time\n"));
	}
	else
		philo->nb_eat = -1;
	gettimeofday(&(philo->tv), NULL);
	*philo_threads = malloc(sizeof(pthread_t) * philo->nb_philo);
	if (!*philo_threads)
		return (printf("Error: malloc failed\n"));
	philo->i = 1;
	if (init_mutexes(philo))
	{
		free(*philo_threads);
		return (1);
	}
	return (0);
}

long int	get_time(struct timeval tv)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec - tv.tv_sec) * 1000 + (current.tv_usec - tv.tv_usec) / 1000);
}

void	*philosopher(void *philo)
{
	int				i;
	int				eaten;

	pthread_mutex_lock(&(((t_philo *)philo)->mutex));
	i = ((t_philo *)philo)->i++;
	pthread_mutex_unlock(&(((t_philo *)philo)->mutex));
	eaten = 0;
	while (((t_philo *)philo)->nb_eat == -1 || eaten++ < ((t_philo *)philo)->nb_eat)
	{
		printf(YELLOW"%ld %d is thinking\n"END, get_time(((t_philo *)philo)->tv), i);
		pthread_mutex_lock(&(((t_philo *)philo)->forks[(i - 1)]));
		pthread_mutex_lock(&(((t_philo *)philo)->forks[i % ((t_philo *)philo)->nb_philo]));
		printf("%ld %d has taken a fork\n", get_time(((t_philo *)philo)->tv), i);
		printf("%ld %d has taken a fork\n", get_time(((t_philo *)philo)->tv), i);
		printf(GREEN"%ld %d is eating\n"END, get_time(((t_philo *)philo)->tv), i);
		usleep(((t_philo *)philo)->time_to_eat * 1000);
		pthread_mutex_unlock(&(((t_philo *)philo)->forks[i % ((t_philo *)philo)->nb_philo]));
		pthread_mutex_unlock(&(((t_philo *)philo)->forks[(i - 1)]));
		printf(BLUE"%ld %d is sleeping\n"END, get_time(((t_philo *)philo)->tv), i);
		usleep(((t_philo *)philo)->time_to_sleep * 1000);
	}
	printf(YELLOW"%ld %d is thinking\n"END, get_time(((t_philo *)philo)->tv), i);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo		philo;
	pthread_t	*philo_threads;
	int			i;

	if (parsing(&philo, argc, argv, &philo_threads))
		return (1);
	i = 0;
	while (i < philo.nb_philo)
		pthread_create(&(philo_threads[i++]), NULL, &philosopher, &philo);
	philo.i = 0;
	i = -1;
	while (++i < philo.nb_philo)
		pthread_join(philo_threads[i++], NULL);
	pthread_mutex_destroy(&(philo.mutex));
	i = -1;
	while (++i < philo.nb_philo)
		pthread_mutex_destroy(&(philo.forks[i]));
	free(philo.forks);
	free(philo_threads);
	printf("All philosophers have eaten enough\n");
	return (0);
}
