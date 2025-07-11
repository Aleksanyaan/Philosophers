#include "./includes/philo.h"

void	init_forks(t_args *args)
{
	int	i;

	pthread_mutex_init(&args->print_mutex, NULL);
	args->forks = malloc(sizeof(pthread_mutex_t)
			* args->number_of_philosophers);
	if (!args->forks)
		return ;
	i = 0;
	while (i < args->number_of_philosophers)
	{
		pthread_mutex_init(&args->forks[i], NULL);
		i++;
	}
}

t_philo	*init_philos(t_args *args)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * args->number_of_philosophers);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < args->number_of_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = get_time_ms();
		philos[i].args = args;
		philos[i].left_fork = &args->forks[i];
		philos[i].right_fork = &args->forks[(i + 1)
			% args->number_of_philosophers];
		i++;
	}
	return (philos);
}

t_args	*init_args(int argc, char *argv[])
{
	t_args *args;

	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	args->number_of_philosophers = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->number_of_times_each_philosopher_must_eat = -1;
	if (argc == 6)
		args->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	args->start_time = get_time_ms();
	args->stop_simulation = 0;
	return (args);
}

void	*print(void *arg)
{
	(void)arg;
	printf("Thread is created!\n");
	return (NULL);
}
