#include "philosophers.h"

static void free_all(t_mon *monitor, t_philo *philos)
{
    free(monitor->forks);
    free(philos);
}

int eat(t_philo *philo, t_mon *monitor)
{
    if (monitor->nb == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        print_action(monitor, philo->id, "has taken a fork");
        ft_usleep(monitor, monitor->time_die);
        return (0);
    }
    if (philo->id % 2 == 0)
        usleep(100);
    take_fork(philo);
    if (monitor->dead)
        return (0);
    pthread_mutex_lock(&monitor->print);
    philo->last_meal = get_time();
    pthread_mutex_unlock(&monitor->print);
    if (monitor->dead)
        return (0);
    print_action(monitor, philo->id, "is eating");
    ft_usleep(monitor, monitor->time_eat);
    reset_fork(philo);
    philo->meals += 1;
    return (1);
}

void *philosopher_loop(void *args)
{
    t_philo *philo;
    t_mon *monitor;

    philo = (t_philo *) args;
    monitor = philo->monitor;
    while (!monitor->dead)
    {
        if (!eat(philo, monitor))
            break ;
        if (monitor->must_eat != -1 && philo->meals == monitor->must_eat)
            break ;
        print_action(monitor, philo->id, "is sleeping");
        ft_usleep(monitor, monitor->time_sleep);
        print_action(monitor, philo->id, "is thinking");
    }
    reset_fork(philo);
    return (NULL);
}

void create_join_threads(int nb_philo, t_philo *philos)
{
    pthread_t   mon_thread;
    int i;

    i = 0;
    while (i < nb_philo)
    {
        pthread_create(&philos[i].thread, NULL, philosopher_loop, &philos[i]);
        i++;
    }
    pthread_create(&mon_thread, NULL, monitor_loop, philos);
    i = 0;
    while (i < nb_philo)
    {
        pthread_join(philos[i].thread, NULL);
        i++;
    }
    pthread_join(mon_thread, NULL);
}

int do_philosophers(int ac, char **av)
{
    t_mon monitor;
    t_philo *philos;
    int i;

    monitor = init_monitor(ac, av);
    if  (!monitor.forks)
        return (-1);
    monitor.start_time = get_time();
    philos = init_philos(&monitor);
    if (!philos)
        return (free(monitor.forks), -1);
    create_join_threads(monitor.nb, philos);
    i = 0;
    while(i < monitor.nb)
    {
        pthread_mutex_destroy(&monitor.forks[i]);
        i++;
    }
    pthread_mutex_destroy(&monitor.print);
    return (free_all(&monitor, philos), 0);
}
