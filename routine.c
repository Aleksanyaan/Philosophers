#include "./includes/philo.h"

int	must_eat_monitor(void *data)
{
	t_args	*args;

	args = (t_args *)data;
	while (1)
	{
		usleep(100);
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
			printf("%ld All philosophers have eaten %d times\n",
				get_time_ms() - args->start_time, args->must_eat_number);
			return (pthread_mutex_unlock(&args->print_mutex), 0);
		}
		else
			pthread_mutex_unlock(&args->meals_eaten_mutex);
	}
	return (0);
}

long	get_time_since_last_meal(t_philo *philo)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&philo->args->last_meal_mutex);
	time_since_last_meal = get_time_ms() - philo->last_meal;
	pthread_mutex_unlock(&philo->args->last_meal_mutex);
	return (time_since_last_meal);
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
			time_since_last_meal = get_time_since_last_meal(&args->philo[i]);
			if (time_since_last_meal > args->time_to_die)
			{
				stop_simulation(args);
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
	if (philo->id % 2 == 0)
		usleep(1000);
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
