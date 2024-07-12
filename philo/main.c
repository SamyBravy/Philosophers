/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:09:34 by samy_bravy        #+#    #+#             */
/*   Updated: 2024/07/12 15:15:24 by sdell-er         ###   ########.fr       */
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

int	init(t_philo *philo, pthread_t **philo_threads, int argc, char **argv)
{
	philo->nb_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]) * 1000;
	philo->time_to_eat = ft_atoi(argv[3]) * 1000;
	philo->time_to_sleep = ft_atoi(argv[4]) * 1000;
	philo->nb_eat = -1;
	if (argc == 6)
		philo->nb_eat = ft_atoi(argv[5]);
	*philo_threads = malloc(sizeof(pthread_t) * philo->nb_philo);
	if (!*philo_threads)
		return (printf("Error: malloc failed\n"));
	pthread_mutex_init(&(philo->mutex), NULL);
	pthread_mutex_init(&(philo->print), NULL);
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->nb_philo);
	if (!philo->forks)
	{
		pthread_mutex_destroy(&(philo->mutex));
		free(*philo_threads);
		return (printf("Error: malloc failed\n"));
	}
	philo->i = 0;
	while (philo->i < philo->nb_philo)
		pthread_mutex_init(&(philo->forks[philo->i++]), NULL);
	philo->i = 1;
	philo->dead = 0;
	return (0);
}

long int	get_time(struct timeval tv)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec - tv.tv_sec) * 1000 + (current.tv_usec - tv.tv_usec) / 1000);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	return (1);
}

int	print(t_philo *philo, int i, char *str, int *last_meal)
{
	pthread_mutex_lock(&(philo->mutex));
	if (philo->dead)
	{
		pthread_mutex_unlock(&(philo->mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->mutex));
	if (get_time(philo->tv) - *last_meal > (philo->time_to_die) / 1000 + 2)
	{
		pthread_mutex_lock(&(philo->mutex));
		philo->dead = i;
		pthread_mutex_unlock(&(philo->mutex));
		pthread_mutex_lock(&(philo->mutex));
		if (philo->dead != i)
		{
			pthread_mutex_unlock(&(philo->mutex));
			return (1);
		}
		pthread_mutex_unlock(&(philo->mutex));
		pthread_mutex_lock(&(philo->print));
		printf("%ld %d %s\n", get_time(philo->tv), i, DIE);
		pthread_mutex_unlock(&(philo->print));
		return (1);
	}
	if (!ft_strcmp(str, EAT))
		*last_meal = get_time(philo->tv);
	pthread_mutex_lock(&(philo->mutex));
	if (philo->dead)
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

int	get_fork(int nb_philo, int i, int k)
{
	if (i == nb_philo && k == 1)
		return (0);
	else if (i == nb_philo && k == 2)
		return (nb_philo - 1);
	else if (k == 1)
		return (i - 1);
	else
		return (i);
}

void	*philosopher(void *philosopher)
{
	int		i;
	int		eaten;
	int		last_meal;
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	pthread_mutex_lock(&(philo->mutex));
	i = philo->i++;
	pthread_mutex_unlock(&(philo->mutex));
	eaten = 0;
	last_meal = 0;
	if (i % 2)
		usleep(100);
	while (philo->nb_eat == -1 || eaten++ < philo->nb_eat)
	{
		pthread_mutex_lock(&(philo->forks[get_fork(philo->nb_philo, i, 1)])); // caso in cui c'e' solo un filosofo
		if (print(philo, i, FORK, &last_meal))
		{
			pthread_mutex_unlock(&(philo->forks[get_fork(philo->nb_philo, i, 1)]));
			return (NULL);
		}
		pthread_mutex_lock(&(philo->forks[get_fork(philo->nb_philo, i, 2)]));
		if (print(philo, i, FORK, &last_meal))
		{
			pthread_mutex_unlock(&(philo->forks[get_fork(philo->nb_philo, i, 2)]));
			pthread_mutex_unlock(&(philo->forks[get_fork(philo->nb_philo, i, 1)]));
			return (NULL);
		}
		if (print(philo, i, EAT, &last_meal))
		{
			pthread_mutex_unlock(&(philo->forks[get_fork(philo->nb_philo, i, 2)]));
			pthread_mutex_unlock(&(philo->forks[get_fork(philo->nb_philo, i, 1)]));
			return (NULL);
		}
		usleep(philo->time_to_eat);
		pthread_mutex_unlock(&(philo->forks[get_fork(philo->nb_philo, i, 2)]));
		pthread_mutex_unlock(&(philo->forks[get_fork(philo->nb_philo, i, 1)]));
		if (eaten == philo->nb_eat)
			return (NULL);
		if (print(philo, i, SLEEP, &last_meal))
			return (NULL);
		usleep(philo->time_to_sleep);
		if (print(philo, i, THINK, &last_meal))
			return (NULL);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo		philo;
	pthread_t	*philo_threads;
	int			i;

	if (parsing(argc, argv))
		return (1);
	if (init(&philo, &philo_threads, argc, argv))
		return (1);
	i = 0;
	gettimeofday(&(philo.tv), NULL);
	while (i < philo.nb_philo)
		pthread_create(&(philo_threads[i++]), NULL, philosopher, &philo);
	i = -1;
	while (++i < philo.nb_philo)
		pthread_join(philo_threads[i], NULL);
	pthread_mutex_destroy(&(philo.mutex));
	pthread_mutex_destroy(&(philo.print));
	i = -1;
	while (++i < philo.nb_philo)
		pthread_mutex_destroy(&(philo.forks[i]));
	free(philo.forks);
	free(philo_threads);
	printf("End\n");
	return (0);
}
