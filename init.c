#include "./includes/philo.h"

void	init_forks(t_args *args)
{
	int	i;

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

void	*print(void *arg)
{
	(void)arg;
	printf("Thread is created!\n");
	return (NULL);
}

void	create_philos(t_philo *philo, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		if (pthread_create(&philo[i].thread, NULL, print,
				&philo[i]))
			return ;
		usleep(500);
		i++;
	}
}
