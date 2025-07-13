#include "./includes/philo.h"

void	free_args(t_args *args)
{
	int i;

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
	if (args->philo)
	{
		free(args->philo);
		args->philo = NULL;
	}

	free(args);
}
