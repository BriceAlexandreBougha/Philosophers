/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbougha <bbougha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:44:59 by bbougha           #+#    #+#             */
/*   Updated: 2025/12/01 13:44:59 by bbougha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_mon
{
	int				nb;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				must_eat;
	long			start_time;
	int				dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}	t_mon;

typedef struct s_philo
{
	int				id;
	int				meals;
	long			last_meal;
	pthread_t		thread;
	t_mon			*monitor;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

t_mon	init_monitor(int ac, char **av);
t_philo	*init_philos(t_mon *monitor);
int		do_philosophers(int ac, char **av);
void	print_action(t_mon *monitor, int id, char *action);
long	get_time(void);
void	ft_usleep(t_mon *monitor, long duration);
void	take_fork(t_philo *philo);
void	reset_fork(t_philo *philo);
void	*monitor_loop(void *arg);
int		ft_atoi(const char *str);
long	ft_atol(const char *str);

#endif