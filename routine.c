#include "./includes/philo.h"

int	is_all_eaten(t_args *args)
{
	int	i;
	int	finished;

	if (args->must_eat_number == -1)
		return (0);
	finished = 0;
	i = 0;
	while (i < args->number_of_philosophers)
	{
		pthread_mutex_lock(&args->meals_eaten_mutex);
		if (args->philo[i].meals_eaten >= args->must_eat_number)
			finished++;
		pthread_mutex_unlock(&args->meals_eaten_mutex);
		i++;
	}
	if (finished == args->number_of_philosophers)
	{
		stop_simulation(args);
		pthread_mutex_lock(&args->print_mutex);
		printf("All philosophers have eaten %d times\n", args->must_eat_number);
		pthread_mutex_unlock(&args->print_mutex);
		return (1);
	}
	return (0);
}

void	get_time_since_last_meal(t_args *args)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&args->last_meal_mutex);
	time_since_last_meal = get_time_ms() - args->philo[i].last_meal;
	pthread_mutex_unlock(&args->last_meal_mutex);
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
			time_since_last_meal = get_time_since_last_meal(args);
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
		if (is_all_eaten(args))
			break ;
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
		if (philo->args->must_eat_number != -1
			&& philo->meals_eaten >= philo->args->must_eat_number)
			break ;
		print_status(philo, "is sleeping");
		usleep(philo->args->time_to_sleep * 1000);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
