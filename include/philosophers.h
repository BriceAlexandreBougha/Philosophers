#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_mon {
    int             nb;
    long            time_die;
    long            time_eat;
    long            time_sleep;
    int             must_eat;
    long            start_time;
    int             dead;
    pthread_mutex_t *forks;
    pthread_mutex_t print;
}               t_mon;

typedef struct s_philo {
    int         id;
    int         meals;
    long        last_meal;
    pthread_t   thread;
    t_mon       *monitor;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
}               t_philo;

t_mon init_monitor(int ac, char **av);
t_philo *init_philos(t_mon *monitor);
int do_philosophers(int ac, char **av);
void print_action(t_mon *monitor, int id, char *action);
long get_time();
void ft_usleep(t_mon *monitor, long duration);
void take_fork(t_philo *philo);
void reset_fork(t_philo *philo);
void *monitor_loop(void *arg);

#endif