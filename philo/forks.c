/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:28:02 by zaleksan          #+#    #+#             */
/*   Updated: 2025/08/11 13:28:03 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->args->last_meal_mutex);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->args->last_meal_mutex);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	print_status(philo, "is eating");
	ft_usleep(philo, philo->args->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (!is_simulation_stopped(philo->args)
		&& ++philo->meals_eaten == philo->args->must_eat_number)
	{
		pthread_mutex_lock(&philo->args->meals_eaten_mutex);
		philo->args->full_philos_count++;
		pthread_mutex_unlock(&philo->args->meals_eaten_mutex);
	}
}
