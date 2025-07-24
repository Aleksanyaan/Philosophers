#include "./includes/philo.h"

int	is_simulation_stopped(t_args *args)
{
	int	result;

	pthread_mutex_lock(&args->stop_mutex);
	result = args->stop_simulation;
	pthread_mutex_unlock(&args->stop_mutex);
	return (result);
}

int	death_monitor(void *data)
{
	int		i;
	t_args	*args;
	long	time_since_last_meal;

	args = (t_args *)data;
	while (!is_simulation_stopped(args))
	{
		i = 0;
		while (i < args->number_of_philosophers)
		{
			if (pthread_mutex_lock(&args->last_meal_mutex) != 0)
				return (1);
			time_since_last_meal = get_time_ms() - args->philo[i].last_meal;
			pthread_mutex_unlock(&args->last_meal_mutex);
			if (time_since_last_meal > args->time_to_die)
			{
				pthread_mutex_lock(&args->stop_mutex);
				args->stop_simulation = 1;
				pthread_mutex_unlock(&args->stop_mutex);
				pthread_mutex_lock(&args->print_mutex);
				printf("%ld %d died\n", get_time_ms() - args->start_time,
					args->philo[i].id);
				pthread_mutex_unlock(&args->print_mutex);
				return (1);
			}
			i++;
		}
		usleep(1000);
	}
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->args->stop_mutex);
		if (philo->args->stop_simulation)
		{
			pthread_mutex_unlock(&philo->args->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->args->stop_mutex);
		eat(philo);
		if (philo->args->number_of_times_each_philosopher_must_eat != -1
			&& philo->meals_eaten >= philo->args->number_of_times_each_philosopher_must_eat)
			break ;
		print_status(philo, "is sleeping");
		usleep(philo->args->time_to_sleep * 1000);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
