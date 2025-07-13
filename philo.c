#include "./includes/philo.h"

void	create_philos(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		if (pthread_create(&args->philo[i].thread, NULL, philo_routine,
				&args->philo[i]))
			return ;
		usleep(500);
		i++;
	}
}

void	join_philos(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		pthread_join(args->philo[i].thread, NULL);
		++i;
	}
}