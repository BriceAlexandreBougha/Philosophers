#include "philosophers.h"

static int check_all_eat(t_philo *philos, t_mon *monitor)
{
    int i;
    int all_eat;

    all_eat = 1;
    if (monitor->must_eat != -1)
    {
        i = 0;
        while (i < monitor->nb)
        {
            if (philos[i].meals < monitor->must_eat)
                all_eat = 0;
            if (!all_eat)
                return (monitor->dead = 1, 0);
            i++;
        }
    }
    return (1);
}

static int check_dead(t_philo *philos, t_mon *monitor)
{
    long now;
    int i;

    i = 0;
    while (i < monitor->nb)
    {
        now = get_time();
        pthread_mutex_lock(&monitor->print);
        if (philos[i].last_meal - now > monitor->time_die)
        {
            monitor->dead = 1;
            printf("%ld %d died\n", now - monitor->start_time, i + 1);
            return (pthread_mutex_unlock(&monitor->print), 0);
        }
        pthread_mutex_unlock(&monitor->print);
        i++;
    }
    return (1);
}

void *monitor_loop(void *arg)
{
    t_philo *philos;
    t_mon   *monitor;

    philos = (t_philo *) arg;
    monitor = philos[0].monitor;
    while (!monitor->dead)
    {
        if (!check_dead(philos, monitor) ||
            !check_all_eat(philos, monitor))
            return (NULL);
        usleep(1000);
    }
    return (NULL);
}