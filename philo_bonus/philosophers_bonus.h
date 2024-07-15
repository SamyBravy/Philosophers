/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:23:01 by sdell-er          #+#    #+#             */
/*   Updated: 2024/07/15 19:21:52 by sdell-er         ###   ########.fr       */
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
	sem_t			*forks;
	sem_t			*is_dead;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	sem_t			*last_meal_sem;
	sem_t			*dead_sem;
	sem_t			*print;
	struct timeval	tv;
}	t_philo;

int			parsing(int argc, char **argv);

int			ft_atoi(const char *nptr);

void		philosopher(t_philo *philo);

long int	get_time(struct timeval tv);
int			print(t_philo *philo, char *str);
void		*check_death(void *philo);
void		*check_starvation(void *philosopher);

#endif
