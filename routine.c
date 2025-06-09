/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:47:31 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/09 12:11:44 by ipavlov          ###   ########.fr       */
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

int	philo_eat(t_philo *philo)
{
	time_t	time_to_eat;

	time_to_eat = get_time_to_eat(philo);
	pthread_mutex_lock(&philo->personal_mutex);
	philo->time_from_last_meal = get_time();
	printf("philo ID: %d: start eating time: %ld // eating time: ==> %ld <==\n",  philo->philo_id, philo->time_from_last_meal, time_to_eat);
	philo->num_of_meals++;
	pthread_mutex_unlock(&philo->personal_mutex);

	// pthread_mutex_lock(&philo->manager->printf);
	// printf("before real TIme: %ld: is eating after USLEEP: %ld\n",  get_time(), philo->time_from_last_meal - philo->manager->start_time);
	// pthread_mutex_unlock(&philo->manager->printf);
	usleep(time_to_eat * 1000);
	// pthread_mutex_lock(&philo->manager->printf);
	// printf("after real TIme: %ld: is eating after USLEEP: %ld\n", get_time(), philo->time_from_last_meal - philo->manager->start_time);
	// pthread_mutex_unlock(&philo->manager->printf);
	
	pthread_mutex_unlock(philo->right_f);
	pthread_mutex_unlock(philo->left_f);
	
	return (0);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->manager->printf);
	printf("philo ID: %d: is sleeping\n\n",  philo->philo_id);
	pthread_mutex_unlock(&philo->manager->printf);
	usleep(philo->time_to_sleep * 1000);

	// yes!! get out od the ram  sleep to check if your dead
//	unsigned long start = get_time();
//	while (get_time() - start < philo->time_to_sleep)
//	{
//		if (check_if_dead(philo)) // check against time_to_die
//			break;
//		usleep(1000); // sleep in 1ms steps
//	}
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->manager->printf);
	printf("philo ID: %d: is thinking: %ld\n\n",  philo->philo_id, get_time());
	pthread_mutex_unlock(&philo->manager->printf);
	// of time to sleep - 100 microseconds or more or calculate it somehow... or nothing
	usleep(100);
}

int	exit_thread(t_philo *philo)
{
	if (philo_dead_f(philo) == 1)
		return (1);
	if (global_grim_dead_f(philo->manager) == 1)
		return (1);
	return (0);
}

void *routine(void *catch_philo)
{
	t_philo		*philo;

	philo = (t_philo *)catch_philo;
	int i = 0;
	// to avoid deadlock, the even philosophers will wait a bit before taking the forks
	if  (philo->philo_id % 2 == 0)
		usleep(1000);
	while(!is_all_dead(philo->manager) && !philo_meal_allowence(philo) && i < 10)
	{
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
		i++;
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
