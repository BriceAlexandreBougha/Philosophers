#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_rules {
    int             nb;
    long            time_die;
    long            time_eat;
    long            time_sleep;
    int             must_eat; // -1 si non précisé
    long            start_time;
    int             someone_died;
    pthread_mutex_t *forks;   // tableau de nb mutex
    pthread_mutex_t print_lock;
}               t_rules;

typedef struct s_philo {
    int         id;
    int         meals;
    long        last_meal; // ms depuis start_time
    pthread_t   thread;
    t_rules     *rules;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
}               t_philo;

#endif