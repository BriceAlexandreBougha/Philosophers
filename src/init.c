#include "philosophers.h"

t_mon init_monitor(int ac, char **av)
{
    t_mon monitor;

    monitor.nb = atoi(av[1]);
    monitor.time_die = atol(av[2]);
    monitor.time_eat = atol(av[3]);
    monitor.time_sleep = atol(av[4]);
    monitor.must_eat = -1;
    monitor.dead = 0;
    if (ac == 6)
        monitor.must_eat = atoi(av[5]);
    monitor.forks = malloc(sizeof(pthread_mutex_t) * monitor.nb);
    for (int i = 0; i < monitor.nb; i++)
        pthread_mutex_init(&monitor.forks[i], NULL);
    pthread_mutex_init(&monitor.print, NULL);
    return (monitor);
}

t_philo *init_philos(t_mon *monitor)
{
    t_philo *philos;
    int i;

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
        i++;
    }
    return (philos);
}
