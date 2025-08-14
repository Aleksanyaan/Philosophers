/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:27:54 by zaleksan          #+#    #+#             */
/*   Updated: 2025/08/14 16:25:12 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int					must_eat_number;
	long				start_time;
	int					stop_simulation;
	int					full_philos_count;
	pthread_mutex_t		full_philos_mutex;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		last_meal_mutex;
	pthread_mutex_t		meals_eaten_mutex;
	pthread_mutex_t		stop_mutex;
	pthread_mutex_t		*forks;
	t_philo				*philo;
	pthread_t			die_monitor_thread;
	pthread_t			must_eat_monitor_thread;
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

int						ft_atoi(const char *str);
int						parsing(int argc, char *argv[]);
int						init_mutexes(t_args *args);
t_args					*init_args(int argc, char *argv[]);
int						init_philos(t_args *args);
void					create_philos(t_args *args);
void					join_philos(t_args *args);
void					print_status(t_philo *philo, const char *msg);
long					get_time_ms(void);
void					ft_usleep(t_philo *philo, long time);
void					stop_simulation(t_args *args);
int						is_simulation_stopped(t_args *args);
void					take_forks(t_philo *philo);
void					eat(t_philo *philo);
void					*philo_routine(void *arg);
int						death_monitor(void *data);
int						must_eat_monitor(void *data);
void					free_args(t_args *args);

#endif