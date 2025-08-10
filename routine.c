#include "./includes/philo.h"

long	get_time_since_last_meal(t_philo *philo)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&philo->args->last_meal_mutex);
	time_since_last_meal = get_time_ms() - philo->last_meal;
	pthread_mutex_unlock(&philo->args->last_meal_mutex);
	return (time_since_last_meal);
}

int	must_eat_monitor(void *data)
{
	t_args	*args;

	args = (t_args *)data;
	while (1)
	{
		pthread_mutex_lock(&args->stop_mutex);
		if (args->stop_simulation)
			return (pthread_mutex_unlock(&args->stop_mutex), 0);
		pthread_mutex_unlock(&args->stop_mutex);
		pthread_mutex_lock(&args->meals_eaten_mutex);
		if (args->full_philos_count == args->number_of_philosophers)
		{
			pthread_mutex_unlock(&args->meals_eaten_mutex);
			stop_simulation(args);
			pthread_mutex_lock(&args->print_mutex);
			printf("%ld All philosophers have eaten %d times\n", get_time_ms()
				- args->start_time, args->must_eat_number);
			args->stop_simulation = 1;
			return (pthread_mutex_unlock(&args->print_mutex), 0);
		}
		else
			pthread_mutex_unlock(&args->meals_eaten_mutex);
		usleep(500);
	}
	return (0);
}

int	death_monitor(void *data)
{
	int		i;
	t_args	*args;

	args = (t_args *)data;
	while (!is_simulation_stopped(args))
	{
		usleep(500);
		i = -1;
		while (++i < args->number_of_philosophers)
		{
			if (get_time_since_last_meal(&args->philo[i]) > args->time_to_die)
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
		}
	}
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->args->last_meal_mutex);
	philo->last_meal = philo->args->start_time;
	pthread_mutex_unlock(&philo->args->last_meal_mutex);
	if (philo->id % 2 == 0)
		usleep(10000);
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
		if (philo->args->must_eat_number != -1
			&& philo->meals_eaten >= philo->args->must_eat_number)
			break ;
		print_status(philo, "is sleeping");
		usleep(philo->args->time_to_sleep * 1000);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
