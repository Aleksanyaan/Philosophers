#include "./includes/philo.h"

void	print_philos(t_philo *philos, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		printf("Philosopher %d:\n", philos[i].id);
		printf("  Left fork address: %p\n", (void *)philos[i].left_fork);
		printf("  Right fork address: %p\n", (void *)philos[i].right_fork);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_args *args;
	t_philo	*philos;

	args = malloc(sizeof(t_args));
	if (!args)
		return (1);
	if (!parsing(argc, argv, args))
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
	philos = init_philos(args);
	print_philos(philos, args);
	create_philos(philos, args);
	// int i = 0;
	// while (i < args->number_of_philosophers) 
	// {
    //     pthread_join(&philos->thread[i], NULL);
	// 	i++;
    // }
	return (0);
}