#include "./includes/philo.h"

void	print_philos(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		printf("Philosopher %d:\n", args->philo[i].id);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_args *args;

	args = init_args(argc, argv);
	if (!parsing(argc, args))
		return (1);
	printf("Parsed OK:\n");
	printf("Philosophers: %d\n", args->number_of_philosophers);
	printf("Time to die: %d\n", args->time_to_die);
	printf("Time to eat: %d\n", args->time_to_eat);
	printf("Time to sleep: %d\n", args->time_to_sleep);
	if (args->number_of_times_each_philosopher_must_eat != -1)
		printf("Meals required: %d\n", args->number_of_times_each_philosopher_must_eat);
	else
		printf("Meals required: unlimited\n");

	init_forks(args);
	init_philos(args);
	print_philos(args);
	create_philos(args);
	death_monitor(args);
	join_philos(args);
	free_args(args);
	return (0);
}
