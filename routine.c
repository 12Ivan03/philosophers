/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:47:31 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/17 15:08:59 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	take_fork(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_f);
		printf_forks(philo);
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
	pthread_mutex_lock(&philo->manager->printf);
	printf("%ld %d is thinking\n", get_local_time(philo->manager),philo->philo_id);
	pthread_mutex_unlock(&philo->manager->printf);
	usleep(200);
}

void	odd_first_delay(t_philo *philo)
{
	time_t	time_left_to_die;
	time_left_to_die = philo->time_to_die - time_since_last_meal(philo);
	if (time_left_to_die >= philo->time_to_eat * 1.5)
		usleep(philo->time_to_eat * 1200);
}

void	one_philo_function(t_philo *philo)
{
	special_sleep(philo->time_to_die, philo);
	pthread_mutex_lock(&philo->personal_mutex);
	philo->phil_dead = 1;
	pthread_mutex_unlock(&philo->personal_mutex);
}

void *routine(void *catch_philo)
{
	t_philo		*ph;

	ph = (t_philo *)catch_philo;
	if (ph->manager->nbr_philo == 1)
		one_philo_function(ph);
	// if (ph->manager->nbr_philo %2 == 0 && ph->philo_id % 2 == 1)
	// 	usleep(100);
	if (ph->philo_id % 2 == 1)
		usleep(100);
	while(!global_grim_dead_f(ph->manager) && !philo_meal_allowence(ph) && !philo_dead_f(ph))
	{
		if (ph->manager->nbr_philo % 2 == 1)// && ph->philo_id == 1)
			odd_first_delay(ph);
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
	}
	return (NULL);
}

// // odd numbers
// void	odd_first_delay(t_philo *philo)
// {
// 	time_t	time_left_to_die;
// 	time_left_to_die = philo->time_to_die - time_since_last_meal(philo);
// 	if (time_left_to_die >= philo->time_to_eat * 1.5)
// 		usleep(philo->time_to_eat * 1200);
// }

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
