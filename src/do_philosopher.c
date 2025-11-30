#include "philosophers.h"

static void free_all(t_mon *monitor, t_philo *philos)
{
    free(monitor->forks);
    free(philos);
}

void take_fork(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->left_fork);
        print_action(philo->monitor, philo->id, "");
    }
}

int do_philosophers(int ac, char **av)
{
    t_mon monitor;
    t_philo *philos;

    monitor = init_monitor(ac, av);
    if  (!monitor.forks)
        return (-1);
    philos = init_philos(monitor);
    if (!philos)
        return (free(monitor.forks), -1);
    (void) philos;
    return (free_all(&monitor, philos), 0);
}
