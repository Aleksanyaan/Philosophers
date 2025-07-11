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
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if (res > 2147483647)
			return (-1);
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (res);
}

int	parsing(int argc, t_args *args)
{
	if (argc != 5 && argc != 6)
		return (printf("Wrong number of arguments!\n"), 0);
	if (args->number_of_philosophers < 0 || args->time_to_die < 0
		|| args->time_to_eat < 0 || args->time_to_sleep < 0 || (argc == 6
			&& args->number_of_times_each_philosopher_must_eat < 0))
	{
		printf("Error: invalid arguments\n");
		return (0);
	}
	return (1);
}