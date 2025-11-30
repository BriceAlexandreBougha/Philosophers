#include "philosophers.h"

long get_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

void ft_usleep(t_mon *monitor, long duration)
{
    long start;

    start = get_time();
    while (!monitor->dead)
    {
        if (get_time() - start >= duration)
            break ;
        usleep(100);
    }
}