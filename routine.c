/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:47:31 by ipavlov           #+#    #+#             */
/*   Updated: 2025/02/28 17:49:42 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int	take_right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_f);
	printf("philo right: %p\n",philo->right_f);
	return (1);
}

int	take_left_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_f);
		printf("philo left: %p\n",philo->left_f);
	return (1);
}

int	take_fork(t_philo *philo)
{
	int	time_to_eat;
	if (philo->philo_id % 2 == 0)
	{
		//take first right fork
		take_right_fork(philo);
		take_left_fork(philo);
	}
	else 
	{
		//take first left fort;
		take_left_fork(philo);
		take_right_fork(philo);
	}
	time_to_eat = philo->time_to_eat;
	philo->time_from_last_meal = get_time();
	usleep(time_to_eat);
	pthread_mutex_unlock(philo->right_f);
	pthread_mutex_unlock(philo->left_f);
	return (0);
}

void *routine(void *catch_philo)
{
	t_philo *philo;
	// int i;

	philo = (t_philo *)catch_philo;
	pthread_mutex_lock(&philo->manager->printf);
	
	printf("philo Id: %d\n",philo->philo_id);

	take_fork(philo);

	
	pthread_mutex_unlock(&philo->manager->printf);
	return NULL;
}
