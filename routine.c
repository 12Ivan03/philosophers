/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:47:31 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/04 20:11:01 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

// int	take_right_fork(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->right_f);
// 	printf("philo right: %p\n",philo->right_f);
// 	return (1);
// }

// int	take_left_fork(t_philo *philo)
// {
// 	if (pthread_mutex_lock(philo->left_f) != 0)
// 		return (0);
// 	if ()

// 		printf("philo left: %p\n",philo->left_f);
// 	return (1);
// }

void	printf_forks(t_philo *philo)
{

	pthread_mutex_lock(&philo->manager->printf);
	printf("philo ID: %d: has taken both forks\n",  philo->philo_id);
	pthread_mutex_unlock(&philo->manager->printf);
}

int	take_fork(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		if (pthread_mutex_lock(philo->right_f) != 0)
			return (0);
		if (pthread_mutex_lock(philo->left_f) != 0)
		{
			pthread_mutex_unlock(philo->right_f);
			return (0);
		}
		printf_forks(philo);
	}
	else
	{
		if (pthread_mutex_lock(philo->left_f) != 0)
			return (0);
		if (pthread_mutex_lock(philo->right_f) != 0)
		{
			pthread_mutex_unlock(philo->left_f);
			return (0);
		}
		printf_forks(philo);
	}
	return (1);
}

// int	philo_eat(t_philo *philo)
// {
// 	int	time_to_eat;

// 	time_to_eat = philo->time_to_eat;
// 	philo->time_from_last_meal = get_time();
// 	usleep(time_to_eat);
// 	pthread_mutex_unlock(philo->right_f);
// 	pthread_mutex_unlock(philo->left_f);
// 	return (0);
// }

void *routine(void *catch_philo)
{
	t_philo		*philo;
	t_manager	*grim_man;

	philo = (t_philo *)catch_philo;
	grim_man = (t_manager *)(philo->manager);

	// pthread_mutex_lock(&philo->manager->printf);
	// printf("philo Id: %d\n",philo->philo_id);
	// printf("philo time to die: %d\n", philo->time_to_die);
	// printf("grim_man->dead: %d\n\n", grim_man->dead);
	// pthread_mutex_unlock(&philo->manager->printf);

	int i = 0;
	while(i < 400)//grim_man->dead != 1) // change it then the logic is down.
	{
		//take a fork
		while (!take_fork(philo))
			usleep(100);

		// eat
		usleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->right_f);
		pthread_mutex_unlock(philo->left_f);

		// sleep
		// think

		// check the grim_man->dead if it is == 1
		if (grim_man->dead == 1)
			break ;
		i++;
	}
	// clean the thread and exit

	// pthread_mutex_lock(&philo->personal_mutex);
	// philo->phil_dead = 1;
	// pthread_mutex_unlock(&philo->personal_mutex);
	return (NULL);
}
