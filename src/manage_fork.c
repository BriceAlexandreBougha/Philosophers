/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbougha <bbougha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:36:10 by bbougha           #+#    #+#             */
/*   Updated: 2025/12/01 13:36:10 by bbougha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_fork(t_philo *philo)
{
	if (is_dead(philo->monitor))
		return ;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		philo->left_lock = 1;
		print_action(philo->monitor, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		philo->right_lock = 1;
		print_action(philo->monitor, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		philo->right_lock = 1;
		print_action(philo->monitor, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		philo->left_lock = 1;
		print_action(philo->monitor, philo->id, "has taken a fork");
	}
}

void	reset_fork(t_philo *philo)
{
	if (philo->left_lock)
	{
		pthread_mutex_unlock(philo->left_fork);
		philo->left_lock = 0;
	}
	if (philo->right_lock)
	{
		pthread_mutex_unlock(philo->right_fork);
		philo->right_lock = 0;
	}
}
