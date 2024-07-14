/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:48:46 by marvin            #+#    #+#             */
/*   Updated: 2024/07/12 12:14:03 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

# define DIE "\033[0;31mdied\033[0m"
# define EAT "\033[0;32mis eating\033[0m"
# define THINK "\033[0;33mis thinking\033[0m"
# define SLEEP "\033[0;34mis sleeping\033[0m"
# define FORK "has taken a fork"

typedef struct s_philo
{
	int				i;
	int				dead;
	int				*started_eating;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	struct timeval	tv;
	pthread_mutex_t	mutex;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*started_eating_mutex;
}	t_philo;

void		*philosopher(void *philosopher);

int			parsing(int argc, char **argv);
int			ft_atoi(const char *nptr);

int			check_starvation(t_philo *philo, int i, int last_meal);

int			get_i_fork(int nb_philo, int i, int k);
int			get_i_started_eating(int nb_philo, int i, int k);
int			print(t_philo *philo, int i, char *str);
int			unlock_mutex(t_philo *philo, int i, int k);
long int	get_time(struct timeval tv);

#endif
