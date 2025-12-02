/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbougha <bbougha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:36:18 by bbougha           #+#    #+#             */
/*   Updated: 2025/12/01 13:36:18 by bbougha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead(t_mon *monitor)
{
	pthread_mutex_lock(&monitor->check);
	if (monitor->dead)
		return (pthread_mutex_unlock(&monitor->check), 1);
	return (pthread_mutex_unlock(&monitor->check), 0);

}

int	check_all_eat(t_philo *philos, t_mon *monitor)
{
	int	i;
	int	all_eat;

	all_eat = 1;
	if (monitor->must_eat != -1)
	{
		i = 0;
		while (i < monitor->nb)
		{
			pthread_mutex_lock(&monitor->inc_meals);
			if (philos[i].meals < monitor->must_eat)
				all_eat = 0;
			pthread_mutex_unlock(&monitor->inc_meals);
			if (all_eat)
			{
				pthread_mutex_lock(&monitor->check);
				monitor->dead = 1;
				pthread_mutex_unlock(&monitor->check);
				return (0);
			}
			i++;
		}
	}
	return (1);
}

int	check_dead(t_philo *philos, t_mon *monitor)
{
	long	now;
	int		i;

	i = 0;
	while (i < monitor->nb)
	{
		pthread_mutex_lock(&monitor->print);
		now = get_time();
		if (now - philos[i].last_meal > monitor->time_die)
		{
			pthread_mutex_lock(&monitor->check);
			monitor->dead = 1;
			pthread_mutex_unlock(&monitor->check);
			printf("%ld %d died\n", now - monitor->start_time, i + 1);
			return (pthread_mutex_unlock(&monitor->print), 0);
		}
		pthread_mutex_unlock(&monitor->print);
		i++;
	}
	return (1);
}

void	*monitor_loop(void *arg)
{
	t_philo	*philos;
	t_mon	*monitor;

	philos = (t_philo *)arg;
	monitor = philos[0].monitor;
	while (!monitor->dead)
	{
		if (!check_dead(philos, monitor) || !check_all_eat(philos, monitor))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
