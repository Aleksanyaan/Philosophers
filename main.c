#include "./includes/philo.h"

void	one_philo(t_args *args)
{
	pthread_mutex_lock(&args->stop_mutex);
	printf("%ld 1 has taken a fork\n", get_time_ms() - args->start_time);
	usleep((args->time_to_die + 1) * 1000);
	printf("%ld 1 died\n", get_time_ms() - args->start_time);
	pthread_mutex_unlock(&args->stop_mutex);
	free_args(args);
}

int	main(int argc, char *argv[])
{
	t_args		*args;
	pthread_t	die_monitor_thread;
	pthread_t	must_eat_monitor_thread;

	args = init_args(argc, argv);
	if (!args || !parsing(argc, args))
		return (free_args(args), 1);
	if (args->number_of_philosophers == 1)
		return (one_philo(args), 0);
	create_philos(args);
	if (pthread_create(&die_monitor_thread, NULL, (void *)death_monitor,
			args) != 0 || pthread_create(&must_eat_monitor_thread, NULL,
			(void *)must_eat_monitor, args) != 0)
		return (printf("Error: Failed to create death monitor thread\n"), 1);
	else
	{
		pthread_join(die_monitor_thread, NULL);
		pthread_join(must_eat_monitor_thread, NULL);
	}
	join_philos(args);
	free_args(args);
	return (0);
}
