#include "./includes/philo.h"

int	main(int argc, char *argv[])
{
	t_args *args;

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

	return (0);
}