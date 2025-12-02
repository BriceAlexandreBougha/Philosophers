/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbougha <bbougha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:35:49 by bbougha           #+#    #+#             */
/*   Updated: 2025/12/01 13:35:49 by bbougha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_mon	init_monitor(int ac, char **av)
{
	t_mon	monitor;
	int		i;

	monitor.nb = ft_atoi(av[1]);
	monitor.time_die = ft_atol(av[2]);
	monitor.time_eat = ft_atol(av[3]);
	monitor.time_sleep = ft_atol(av[4]);
	monitor.must_eat = -1;
	monitor.dead = 0;
	if (ac == 6)
		monitor.must_eat = ft_atoi(av[5]);
	monitor.forks = malloc(sizeof(pthread_mutex_t) * monitor.nb);
	if (!monitor.forks)
		return (monitor);
	i = 0;
	while (i < monitor.nb)
	{
		pthread_mutex_init(&monitor.forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&monitor.print, NULL);
	pthread_mutex_init(&monitor.check, NULL);
	pthread_mutex_init(&monitor.inc_meals, NULL);
	return (monitor);
}

t_philo	*init_philos(t_mon *monitor)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(struct s_philo) * (*monitor).nb);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < (*monitor).nb)
	{
		philos[i].id = i + 1;
		philos[i].meals = 0;
		philos[i].last_meal = (*monitor).start_time;
		philos[i].monitor = monitor;
		philos[i].left_fork = &monitor->forks[i];
		philos[i].right_fork = &monitor->forks[(i + 1) % (*monitor).nb];
		philos[i].left_lock = 0;
		philos[i].right_lock = 0;
		i++;
	}
	return (philos);
}
