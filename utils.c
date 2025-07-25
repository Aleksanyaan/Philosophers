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
	pthread_mutex_lock(&philo->args->stop_mutex);
	if (!philo->args->stop_simulation)
		printf("%ld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->args->stop_mutex);
	pthread_mutex_unlock(&philo->args->print_mutex);
}

void	ft_usleep(t_philo *philo, long time)
{
	long	start;
	long	now;

	start = get_time_ms();
	while (1)
	{
		now = get_time_ms();
		if (now - start >= time)
			break ;
		pthread_mutex_lock(&philo->args->stop_mutex);
		if (philo->args->stop_simulation)
		{
			pthread_mutex_unlock(&philo->args->stop_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->args->stop_mutex);
		usleep(100);
	}
}
