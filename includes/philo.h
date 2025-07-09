
#ifndef PHILO_H
# define PHILO_H

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_args
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}		t_args;

int		parsing(int argc, char *argv[], t_args *args);

#endif