
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_args
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
	long				start_time;
	int					stop_simulation;
	pthread_t			thread_die;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		last_meal_mutex;
	pthread_mutex_t		meals_eaten_mutex;
	pthread_mutex_t		stop_mutex;
	pthread_mutex_t		*forks;
	t_philo				*philo;
}						t_args;

typedef struct s_philo
{
	int					id;
	long				last_meal;
	int					meals_eaten;
	pthread_t			thread;
	t_args				*args;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
}						t_philo;

// parsing.c
int						ft_atoi(const char *str);
int						parsing(int argc, t_args *args);

// init.c
void					init_forks(t_args *args);
t_args					*init_args(int argc, char *argv[]);
void					init_philos(t_args *args);

// philo.c
void					create_philos(t_args *args);
void					join_philos(t_args *args);

// utils.h
void					print_status(t_philo *philo, const char *msg);
long					get_time_ms(void);
void					ft_usleep(int ms);

// forks.h
void					take_forks(t_philo *philo);
void					eat(t_philo *philo);

// routine.c
void					*philo_routine(void *arg);

// actions.c
int						death_monitor(void *data);

// free.c
void					free_args(t_args *args);

#endif