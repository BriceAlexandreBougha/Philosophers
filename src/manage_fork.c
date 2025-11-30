#include "philosophers.h"

void take_fork(t_philo *philo)
{
    if (philo->monitor->dead)
        return ;
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->left_fork);
        print_action(philo->monitor, philo->id, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        print_action(philo->monitor, philo->id, "has taken a fork");
    } else
    {
        pthread_mutex_lock(philo->right_fork);
        print_action(philo->monitor, philo->id, "has taken a fork");
        pthread_mutex_lock(philo->left_fork);
        print_action(philo->monitor, philo->id, "has taken a fork");
    }
}

void reset_fork(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}