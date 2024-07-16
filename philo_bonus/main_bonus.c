/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:22:53 by sdell-er          #+#    #+#             */
/*   Updated: 2024/07/16 17:28:07 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static char	*create_string(int i)
{
	static char	str[2];

	str[0] = '0' + i;
	str[1] = '\0';
	return (str);
}

static void	destroy(t_philo *philo)
{
	sem_close(philo->forks);
	sem_close(philo->print);
	sem_close(philo->dead_sem);
	sem_close(philo->is_dead);
	sem_close(philo->last_meal_sem);
	sem_close(philo->eaten_sem);
	philo->j = 0;
	while (philo->j < philo->nb_philo)
		sem_close(philo->finished_eating[philo->j++]);
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("dead_sem");
	sem_unlink("is_dead");
	sem_unlink("last_meal");
	sem_unlink("eaten_sem");
	philo->j = 0;
	while (philo->j < philo->nb_philo)
		sem_unlink(create_string(philo->j++));
	free(philo->finished_eating);
}

static void	init_sem(t_philo *philo)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("dead_sem");
	sem_unlink("is_dead");
	sem_unlink("last_meal");
	sem_unlink("eaten_sem");
	philo->j = 0;
	while (philo->j < philo->nb_philo)
		sem_unlink(create_string(philo->j++));
	philo->forks = sem_open("forks", O_CREAT, 0644, philo->nb_philo);
	philo->print = sem_open("print", O_CREAT, 0644, 1);
	philo->dead_sem = sem_open("dead_sem", O_CREAT, 0644, 1);
	philo->is_dead = sem_open("is_dead", O_CREAT, 0644, 1);
	sem_wait(philo->is_dead);
	philo->last_meal_sem = sem_open("last_meal", O_CREAT, 0644, 1);
	philo->eaten_sem = sem_open("eaten_sem", O_CREAT, 0644, 1);
	philo->finished_eating = malloc(sizeof(sem_t *) * philo->nb_philo);
	philo->j = 0;
	while (philo->j < philo->nb_philo)
	{
		philo->finished_eating[philo->j]
			= sem_open(create_string(philo->j), O_CREAT, 0644, 1);
		sem_wait(philo->finished_eating[philo->j++]);
	}
}

static void	init(t_philo *philo, int argc, char **argv)
{
	philo->nb_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]) * 1000;
	philo->time_to_eat = ft_atoi(argv[3]) * 1000;
	philo->time_to_sleep = ft_atoi(argv[4]) * 1000;
	philo->nb_eat = -1;
	if (argc == 6)
		philo->nb_eat = ft_atoi(argv[5]);
	philo->dead = 0;
	philo->last_meal = 0;
	philo->eaten = 0;
	init_sem(philo);
	gettimeofday(&(philo->tv), NULL);
}

int	main(int argc, char **argv)
{
	t_philo		philo;
	pid_t		pid;

	if (parsing(argc, argv))
		return (1);
	init(&philo, argc, argv);
	philo.i = 1;
	while (philo.i <= philo.nb_philo)
	{
		pid = fork();
		if (pid == 0)
			break ;
		if (pid < 0)
			return (printf("Error: Fork failed\n"));
		philo.i++;
	}
	if (pid == 0)
		philosopher(&philo);
	else
		while (philo.i-- > 1)
			waitpid(-1, NULL, 0);
	destroy(&philo);
	return (0);
}
