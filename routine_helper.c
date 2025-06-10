/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:32:26 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/10 16:48:04 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	printf_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->manager->printf);
	printf("%ld philo ID: %d: has both forks\n", get_local_time(philo->manager), philo->philo_id);
	pthread_mutex_unlock(&philo->manager->printf);
	// printf("philo ID: %d: start time: %ld\n",  philo->philo_id, philo->manager->start_time);
	// printf("philo ID: %d: fork right address: %p\n",  philo->philo_id, philo->right_f);
	// printf("philo ID: %d: fork left address: %p\n",  philo->philo_id, philo->left_f);
}

int	philo_meal_allowence(t_philo *philo)
{
	int num_meals_philo;

	pthread_mutex_lock(&philo->personal_mutex);
	num_meals_philo = philo->num_of_eaten_meals;
	pthread_mutex_unlock(&philo->personal_mutex);

	// pthread_mutex_lock(&philo->manager->printf);
	// printf("===> mum of meals philo: %d\n",num_meals_philo);
	// pthread_mutex_unlock(&philo->manager->printf);

	if (philo->manager->num_of_meals != 0 && \
		num_meals_philo == philo->manager->num_of_meals)
	{
		// pthread_mutex_lock(&philo->personal_mutex);
		// philo->phil_dead = 1;
		// pthread_mutex_unlock(&philo->personal_mutex);
		pthread_mutex_lock(&philo->manager->printf);
		printf("%ld philo ID: %d: has eaten %d meals\n", get_local_time(philo->manager), philo->philo_id, philo->num_of_meals);
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
