/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:47:31 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/11 21:07:00 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	take_fork(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_f);
		if (pthread_mutex_lock(philo->left_f) != 0)
		{
			pthread_mutex_unlock(philo->right_f);
			return (0);
		}
	}
	else
	{
		pthread_mutex_lock(philo->left_f);
		if (pthread_mutex_lock(philo->right_f) != 0)
		{
			pthread_mutex_unlock(philo->left_f);
			return (0);
		}
	}
	printf_forks(philo);
	return (1);
}

void	special_sleep(time_t duration, t_philo *philo)
{
	time_t	start;

	start = get_time();
	while(duration > get_time() - start)
	{
		if (global_grim_dead_f(philo->manager) || philo_dead_f(philo))
		{
			// raise_philo_dead_flag(philo);
			// killer_function(philo->manager);
			break ;
		}
		usleep(500);
	}
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
	printf("%ld philo ID: %d: is eating      ==>last meal - start time :%ld:<==\n", get_local_time(philo->manager), philo->philo_id, philo->time_from_last_meal - philo->manager->start_time);
	pthread_mutex_unlock(&philo->manager->printf);
	special_sleep(time_to_eat, philo);
	pthread_mutex_unlock(philo->right_f);
	pthread_mutex_unlock(philo->left_f);
	return (0);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->manager->printf);
	printf("%ld philo ID: %d: is sleeping\n", get_local_time(philo->manager), philo->philo_id);
	pthread_mutex_unlock(&philo->manager->printf);
	special_sleep(philo->time_to_sleep, philo);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->manager->printf);
	printf("%ld philo ID: %d: is thinking\n", get_local_time(philo->manager), philo->philo_id);
	pthread_mutex_unlock(&philo->manager->printf);
	// of time to sleep - 100 microseconds or more or calculate it somehow... or nothing
	usleep(philo->time_to_sleep / 0.5);
}

// odd numbers
void	odd_first_delay(t_philo *philo)
{
	// calculate how much time is left before dying

	time_t	time_left_to_die;

	time_left_to_die = philo->time_to_die - time_since_last_meal(philo);
	// pthread_mutex_lock(&philo->manager->printf);
	// printf("odd philos [%d]: time left to die: %ld\n", philo->philo_id, time_left_to_die);
	// pthread_mutex_unlock(&philo->manager->printf);
	if (time_left_to_die >= philo->time_to_eat * 1.5)
	{
		pthread_mutex_lock(&philo->manager->printf);
		printf("=>odd philos [%d]: time left to die: %ld\n", philo->philo_id, time_left_to_die);
		pthread_mutex_unlock(&philo->manager->printf);
		usleep(philo->time_to_eat * 1200);
	}
}
// one philo

void *routine(void *catch_philo)
{
	t_philo		*philo;

	philo = (t_philo *)catch_philo;
	// to avoid deadlock, the even philosophers will wait a bit before taking the forks
	// if (philo->manager->nbr_philo %2 == 1 && philo->philo_id %2 == 1)
	// 	special_sleep(philo->time_to_eat, philo);

	if  (philo->philo_id % 2 == 1)
		usleep(100);
	while(!global_grim_dead_f(philo->manager) && !philo_meal_allowence(philo))
	{
		if (philo->manager->nbr_philo % 2 == 1)
			odd_first_delay(philo);
		// add time to accomudte odd numbers og philos
		take_fork(philo);
		if (exit_thread(philo))
			return (NULL);
		philo_eat(philo);
		if (exit_thread(philo))
			return (NULL);
		philo_sleep(philo);
		if (exit_thread(philo))
			return (NULL);
		philo_think(philo);
		if (exit_thread(philo))
			return (NULL);
	}
	return (NULL);
}

// pthread_mutex_lock(&philo->manager->printf);
// printf("philo Id: %d\n",philo->philo_id);
// printf("philo time to die: %d\n", philo->time_to_die);
// printf("grim_man->dead: %d\n\n", grim_man->dead);
// pthread_mutex_unlock(&philo->manager->printf);


	// pthread_mutex_lock(&philo->manager->printf);
	// printf("philo ID: %d: start eating time: %d\n\n",  philo->philo_id, philo->time_from_last_meal);
	// pthread_mutex_unlock(&philo->manager->printf);

	// pthread_mutex_lock(&philo->manager->printf);
	// printf("philo ID: %d: left forks time: %ld\n\n",  philo->philo_id, philo->time_from_last_meal);
	// pthread_mutex_unlock(&philo->manager->printf);
