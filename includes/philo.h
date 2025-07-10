
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_args
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	long			start_time;
	int				stop_simulation;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
}					t_args;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	t_args			*args;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

int					parsing(int argc, char *argv[], t_args *args);
long				get_time_ms(void);
void				init_forks(t_args *args);
t_philo				*init_philos(t_args *args);
void				create_philos(t_philo *philo, t_args *args);

#endif