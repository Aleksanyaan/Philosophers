#include "./includes/philo.h"

int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '\0')
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if (res > 2147483647)
			return (0);
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return (res);
}

int	parsing(int argc, char *argv[], t_args *args)
{
	if (argc != 5 && argc != 6)
		return (write(1, "Wrong number of arguments!\n", 27), 0);
	args->number_of_philosophers = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->number_of_times_each_philosopher_must_eat = -1;
	if (argc == 6)
		args->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if (args->number_of_philosophers <= 0 || args->time_to_die <= 0
		|| args->time_to_eat <= 0 || args->time_to_sleep <= 0 || (argc == 6
			&& args->number_of_times_each_philosopher_must_eat <= 0))
	{
		write(1, "Error: invalid arguments\n", 25);
		return (0);
	}
	return (1);
}