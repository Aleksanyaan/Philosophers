#include "./includes/philo.h"

int	death_monitor(void *data)
{
	int	i;
	t_args	*args;
	
	args = (t_args *)data;
	while (!args->stop_simulation)
	{
		i = 0;
		while (i < args->number_of_philosophers)
		{
			if ((get_time_ms() - args->philo[i].last_meal) > args->time_to_die)
			{
				args->stop_simulation = 1;
				print_status(&args->philo[i], "died");
				return (1);
			}
			i++;
		}
		usleep(1000);
	}
	return (0);
}
