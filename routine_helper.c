/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:32:26 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/13 18:16:08 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	printf_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->manager->printf);
	printf("%ld %d has taken a fork\n", get_local_time(philo->manager), philo->philo_id);
	pthread_mutex_unlock(&philo->manager->printf);
}

int	philo_meal_allowence(t_philo *philo)
{
	int num_meals_philo;

	pthread_mutex_lock(&philo->personal_mutex);
	num_meals_philo = philo->num_of_eaten_meals;
	pthread_mutex_unlock(&philo->personal_mutex);

	if (philo->manager->num_of_meals != 0 && \
		num_meals_philo == philo->manager->num_of_meals)
	{
		pthread_mutex_lock(&philo->manager->printf);
		printf("%ld %d: finished %d meals\n", get_local_time(philo->manager), philo->philo_id, philo->num_of_meals);
		pthread_mutex_unlock(&philo->manager->printf);
		return (1);
	}
	return (0);
}

int	exit_thread(t_philo *philo)
{
	if (philo_dead_f(philo) == 1)
		return (1);
	if (global_grim_dead_f(philo->manager) == 1)
		return (1);
	return (0);
}

void	special_sleep(time_t duration, t_philo *philo)
{
	time_t	start;

	start = get_time();
	while(duration > get_time() - start)
	{
		if (global_grim_dead_f(philo->manager) || philo_dead_f(philo))
			break ;
		usleep(500);
	}
}
