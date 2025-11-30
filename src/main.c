#include "philosophers.h"



int main(int ac, char **av)
{
    if (ac < 5 || ac > 6)
        return (0);
    return (do_philosophers(ac, av));
}