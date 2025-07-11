#include "./includes/philo.h"

void	death_monitor(t_philo *philos, t_args *args)
{
	int	i;

	while (!args->stop_simulation)
	{
		i = 0;
		while (i < args->number_of_philosophers)
		{
			if ((get_time_ms() - philos[i].last_meal) > args->time_to_die)
			{
				args->stop_simulation = 1;
				print_status(&philos[i], "died");
				return ;
			}
			i++;
		}
		usleep(1000);
	}
}
