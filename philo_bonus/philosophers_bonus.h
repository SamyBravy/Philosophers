/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:23:01 by sdell-er          #+#    #+#             */
/*   Updated: 2024/07/16 17:29:26 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <semaphore.h>

# define DIE "\033[0;31mdied\033[0m"
# define EAT "\033[0;32mis eating\033[0m"
# define THINK "\033[0;33mis thinking\033[0m"
# define SLEEP "\033[0;34mis sleeping\033[0m"
# define FORK "has taken a fork"

typedef struct s_philo
{
	int				i;
	int				dead;
	int				last_meal;
	int				eaten;
	sem_t			*forks;
	sem_t			*is_dead;
	sem_t			**finished_eating;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	sem_t			*eaten_sem;
	sem_t			*last_meal_sem;
	sem_t			*dead_sem;
	sem_t			*print;
	int				j;
	struct timeval	tv;
}	t_philo;

int			parsing(int argc, char **argv);

void		philosopher(t_philo *philo);

int			ft_atoi(const char *nptr);
long int	get_time(struct timeval tv);
int			print(t_philo *philo, char *str);
void		wait_finished_eating(t_philo *philo);

void		*check_death(void *philo);
void		*check_starvation(void *philosopher);

#endif
