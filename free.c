#include "./includes/philo.h"

void	free_args(t_args *args)
{
	int	i;

	if (args == NULL)
		return ;
	pthread_mutex_destroy(&args->print_mutex);
	if (args->forks)
	{
		i = 0;
		while (i < args->number_of_philosophers)
			pthread_mutex_destroy(&args->forks[i++]);
		free(args->forks);
		args->forks = NULL;
	}
	free(args);
}