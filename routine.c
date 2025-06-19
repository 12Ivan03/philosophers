/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:47:31 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/19 22:55:11 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	take_fork(t_philo *philo)
{
	if (exit_thread(philo))
			return (0);
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_f);
		printf_forks(philo); // check if dead before printing an dif yes return NULL and exit thread.
		if (pthread_mutex_lock(philo->left_f) != 0)
		{
			pthread_mutex_unlock(philo->right_f);
			return (0);
		}
	}
	else
	{
		pthread_mutex_lock(philo->left_f);
		printf_forks(philo);
		if (pthread_mutex_lock(philo->right_f) != 0)
		{
			pthread_mutex_unlock(philo->left_f);
			return (0);
		}
	}
	printf_forks(philo);
	return (1);
}

int	philo_eat(t_philo *philo)
{
	time_t	time_to_eat;

	time_to_eat = get_time_to_eat(philo);
	pthread_mutex_lock(&philo->personal_mutex);
	philo->time_from_last_meal = get_time();
 	philo->num_of_eaten_meals++;
	pthread_mutex_unlock(&philo->personal_mutex);
	pthread_mutex_lock(&philo->manager->printf);
	printf("%ld %d is eating\n", get_local_time(philo->manager), philo->philo_id);
	pthread_mutex_unlock(&philo->manager->printf);
	special_sleep(time_to_eat, philo);
	pthread_mutex_unlock(philo->right_f);
	pthread_mutex_unlock(philo->left_f);
	return (0);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->manager->printf);
	printf("%ld %d is sleeping\n", get_local_time(philo->manager), philo->philo_id);
	pthread_mutex_unlock(&philo->manager->printf);
	special_sleep(philo->time_to_sleep, philo);
}

void	philo_think(t_philo *philo)
{
	// int	delay;

	// if (philo->time_to_eat < philo->time_to_sleep)
	// 	delay = philo->time_to_eat / 2;
	// else
		// delay = philo->time_to_sleep / 2;
	pthread_mutex_lock(&philo->manager->printf);
	printf("%ld %d is thinking\n", get_local_time(philo->manager),philo->philo_id);
	pthread_mutex_unlock(&philo->manager->printf);
	// if (philo->philo_id == philo->manager->nbr_philo)
	// 	return ;
	// else
	if (philo->philo_id % 2 == 1)
		usleep(1000);
		// usleep(philo->time_to_eat * 500);
	// 	// usleep(100);
	// 	usleep(delay);
	// else if (philo->philo_id % 2 == 0)
	// 	// usleep(100);
	// 	usleep(delay);
	// else
		// usleep(100);
		// usleep(philo->time_to_sleep);
}

void *routine(void *catch_philo)
{
	t_philo		*ph;

	ph = (t_philo *)catch_philo;
	if (ph->manager->nbr_philo == 1)
		one_philo_function(ph);
	// if (ph->manager->nbr_philo % 2 == 0 && ph->philo_id % 2 == 1)
	if (ph->philo_id % 2 == 1)
		usleep(ph->philo_id * 1000 / 2);
	// usleep(ph->time_to_eat * 1000 / 2);
	// if (ph->philo_id % 2 == 0)
	// 	usleep(300);
	// this and
	// if (ph->philo_id % 2 == 1)
	// 	usleep(300);
	// usleep(ph->philo_id * 500 / 2);
	while(!global_grim_dead_f(ph->manager) && !philo_meal_allowence(ph) && !philo_dead_f(ph))
	{
		if (ph->philo_id % 2 == 1 && ph->manager->nbr_philo % 2 == 1) // <--// && ph->philo_id % 2 == 1)
			usleep(ph->time_to_eat * 1000 / 2);
			// odd_first_delay(ph);
		take_fork(ph);
		if (exit_thread(ph))
			return (NULL);
		philo_eat(ph);
		if (exit_thread(ph))
			return (NULL);
		philo_sleep(ph);
		if (exit_thread(ph))
			return (NULL);
		philo_think(ph);
		if (exit_thread(ph))
			return (NULL);
		// if (get_local_time(ph->manager) > ph->time_to_die * 1.5)
	}
	return (NULL);
}
