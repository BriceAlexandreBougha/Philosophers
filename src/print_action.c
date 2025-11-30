#include "philosophers.h"

void print_action(t_mon *monitor, int id, char *action)
{
    long time_from_start;

    pthread_mutex_lock(&monitor->print);
    if (!monitor->dead)
    {
        time_from_start = get_time() - monitor->start_time;
        printf("%lld %d %s\n", time_from_start, id, action);
    }
    pthread_mutex_unlock(&monitor->print);
}