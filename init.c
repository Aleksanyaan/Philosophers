#include "./includes/philo.h"

int	init_mutexes(t_args *args)
{
	int	i;

	pthread_mutex_init(&args->print_mutex, NULL);
	pthread_mutex_init(&args->stop_mutex, NULL);
	pthread_mutex_init(&args->last_meal_mutex, NULL);
	pthread_mutex_init(&args->meals_eaten_mutex, NULL);
	args->forks = malloc(sizeof(pthread_mutex_t)
			* args->number_of_philosophers);
	if (!args->forks)
		return (0);
	i = 0;
	while (i < args->number_of_philosophers)
	{
		pthread_mutex_init(&args->forks[i], NULL);
		i++;
	}
	return (1);
}

int	init_philos(t_args *args)
{
	int	i;

	args->philo = malloc(sizeof(t_philo) * args->number_of_philosophers);
	if (!args->philo)
		return (0);
	i = 0;
	while (i < args->number_of_philosophers)
	{
		args->philo[i].id = i + 1;
		args->philo[i].meals_eaten = 0;
		args->philo[i].last_meal = args->start_time;
		args->philo[i].args = args;
		args->philo[i].left_fork = &args->forks[i];
		args->philo[i].right_fork = &args->forks[(i + 1)
			% args->number_of_philosophers];
		i++;
	}
	return (1);
}

t_args	*init_args(int argc, char *argv[])
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	args->number_of_philosophers = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->must_eat_number = -1;
	if (argc == 6)
		args->must_eat_number = ft_atoi(argv[5]);
	args->stop_simulation = 0;
	if (init_mutexes(args) == 0)
		return (free_args(args), NULL);
	args->start_time = get_time_ms();
	if (init_philos(args) == 0)
		return (free_args(args), NULL);
	return (args);
}

void	free_args(t_args *args)
{
	int	i;

	if (!args)
		return ;
	if (args->forks)
	{
		i = 0;
		while (i < args->number_of_philosophers)
		{
			pthread_mutex_destroy(&args->forks[i]);
			i++;
		}
		free(args->forks);
		args->forks = NULL;
	}
	pthread_mutex_destroy(&args->print_mutex);
	pthread_mutex_destroy(&args->stop_mutex);
	pthread_mutex_destroy(&args->last_meal_mutex);
	pthread_mutex_destroy(&args->meals_eaten_mutex);
	if (args->philo)
	{
		free(args->philo);
		args->philo = NULL;
	}
	free(args);
}
