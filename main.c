#include "./includes/philo.h"

int	main(int argc, char *argv[])
{
	t_args		*args;
	pthread_t	monitor_thread;

	args = init_args(argc, argv);
	if (!parsing(argc, args))
		return (1);
	init_forks(args);
	init_philos(args);
	create_philos(args);
	if (pthread_create(&monitor_thread, NULL, (void *(*)(void *))death_monitor,
			args) != 0)
	{
		printf("Error: Failed to create death monitor thread\n");
		free_args(args);
		return (1);
	}
	pthread_join(monitor_thread, NULL);
	join_philos(args);
	free_args(args);
	return (0);
}
