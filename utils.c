#include "./includes/philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_status(t_philo *philo, const char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philo->args->print_mutex);
	timestamp = get_time_ms() - philo->args->start_time;
	if (!philo->args->stop_simulation)
		printf("%ld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->args->print_mutex);
}

void	ft_usleep(int ms)
{
	long	start;
	long	now;

	start = get_time_ms();
	now = get_time_ms();
	while (now - start < ms)
	{
		usleep(100);
		now = get_time_ms();
	}
}
