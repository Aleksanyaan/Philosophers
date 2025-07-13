#include "./includes/philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;

	if (philo->id % 2 == 0)
		usleep(1000);

	while (!philo->args->stop_simulation)
	{
		eat(philo);

		if (philo->args->number_of_times_each_philosopher_must_eat != -1
			&& philo->meals_eaten >= philo->args->number_of_times_each_philosopher_must_eat)
			break;

		print_status(philo, "is sleeping");
		usleep(philo->args->time_to_sleep * 1000);

		print_status(philo, "is thinking");
	}
	return (NULL);
}
