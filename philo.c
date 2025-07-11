#include "./includes/philo.h"

void	create_philos(t_philo *philo, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		if (pthread_create(&philo[i].thread, NULL, philo_routine,
				&philo[i]))
			return ;
		usleep(500);
		i++;
	}
}

void	join_philos(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->args->number_of_philosophers)
	{
		pthread_join(philo[i].thread, NULL);
		++i;
	}
}