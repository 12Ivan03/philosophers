/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:47:31 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/20 20:11:55 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	take_fork(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_f);
		printf_forks(philo); // check if dead before printing an dif yes return NULL and exit thread.
		pthread_mutex_lock(philo->left_f);
	}
	else
	{
		pthread_mutex_lock(philo->left_f);
		printf_forks(philo);
		pthread_mutex_lock(philo->right_f);
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
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_f);
		pthread_mutex_unlock(philo->left_f);
	}
	else
	{
		pthread_mutex_unlock(philo->left_f);
		pthread_mutex_unlock(philo->right_f);
	}
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
	// usleep(200);
	if (philo->manager->nbr_philo % 2 == 1 && philo->philo_id % 2 == 1)
		usleep(1000);
}

void *routine(void *catch_philo)
{
	t_philo		*ph;

	ph = (t_philo *)catch_philo;
	if (ph->manager->nbr_philo == 1)
		one_philo_function(ph);
	// if (ph->manager->nbr_philo %2 == 0 && ph->philo_id % 2 == 1)
	// 	usleep(100);
	if (ph->manager->nbr_philo % 2 == 1 && ph->philo_id % 2 == 1)
		usleep(ph->philo_id * 1000 / 2);
	// this and
	// if (ph->philo_id % 2 == 1)
	// 	usleep(100);
	while(!global_grim_dead_f(ph->manager) && !philo_meal_allowence(ph) && !philo_dead_f(ph))
	{
		if (ph->manager->nbr_philo < 51 && ph->philo_id % 2 == 1 && ph->manager->nbr_philo % 2 == 1)
			usleep(ph->time_to_eat * 1000 / 2);
		else if (ph->philo_id % 2 == 1 && ph->manager->nbr_philo % 2 == 1)
			usleep(200);
		if (ph->manager->nbr_philo > 50 && ph->manager->nbr_philo % 2 == 0 && ph->philo_id % 2 == 1)//this --> ph->manager->nbr_philo % 2 == 1)<--// && ph->philo_id % 2 == 1)
			usleep(100);
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
	}
	return (NULL);
}


// #include <philosophers.h>

// int	take_fork(t_philo *philo)
// {
// 	if (exit_thread(philo))
// 			return (0);
// 	if (philo->philo_id % 2 == 0)
// 	{
// 		pthread_mutex_lock(philo->left_f);
// 		pthread_mutex_lock(philo->right_f);
// 		printf_forks(philo); // check if dead before printing an dif yes return NULL and exit thread.
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(philo->right_f);
// 		pthread_mutex_lock(philo->left_f);
// 		printf_forks(philo);
// 	}
// 	printf_forks(philo);
// 	return (1);
// }

// int	philo_eat(t_philo *philo)
// {
// 	time_t	time_to_eat;

// 	time_to_eat = get_time_to_eat(philo);
// 	pthread_mutex_lock(&philo->personal_mutex);
// 	philo->time_from_last_meal = get_time();
//  	philo->num_of_eaten_meals++;
// 	pthread_mutex_unlock(&philo->personal_mutex);
// 	pthread_mutex_lock(&philo->manager->printf);
// 	printf("%ld %d is eating\n", get_local_time(philo->manager), philo->philo_id);
// 	pthread_mutex_unlock(&philo->manager->printf);
// 	special_sleep(time_to_eat, philo);
// 	if (philo->philo_id % 2 == 0)
// 	{
// 		pthread_mutex_unlock(philo->left_f);
// 		pthread_mutex_unlock(philo->right_f);
// 	}
// 	else
// 	{
// 		pthread_mutex_unlock(philo->right_f);
// 		pthread_mutex_unlock(philo->left_f);
// 	}
// 	return (0);
// }

// void	philo_sleep(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->manager->printf);
// 	printf("%ld %d is sleeping\n", get_local_time(philo->manager), philo->philo_id);
// 	pthread_mutex_unlock(&philo->manager->printf);
// 	special_sleep(philo->time_to_sleep, philo);
// }

// void	philo_think(t_philo *philo)
// {
// 	// int	delay;

// 	// if (philo->time_to_eat < philo->time_to_sleep)
// 	// 	delay = philo->time_to_eat / 2;
// 	// else
// 		// delay = philo->time_to_sleep / 2;
// 	pthread_mutex_lock(&philo->manager->printf);
// 	printf("%ld %d is thinking\n", get_local_time(philo->manager),philo->philo_id);
// 	pthread_mutex_unlock(&philo->manager->printf);
// 	// if (philo->philo_id == philo->manager->nbr_philo)
// 	// 	return ;
// 	// else

// 	// if (philo->philo_id % 2 == 1)
// 		// usleep(1000);

		
// 		// usleep(philo->time_to_eat * 500);
// 	// usleep(500);
// 	// 	usleep(delay);
// 	// else if (philo->philo_id % 2 == 0)
// 	// 	// usleep(100);
// 	// 	usleep(delay);
// 	// else
// 		// usleep(100);
// 		// usleep(philo->time_to_sleep);
// }

// void	ft_sleep(time_t duration, t_philo *p)
// {
// 	time_t	start;
// 	time_t	end;

// 	start = get_time();
// 	end = 100 + 5 * p->philo_id;
// 	while (start - get_time() < duration)
// 	{
// 		usleep(end);
// 	}
// 	// usleep(1000);
// }

// void *routine(void *catch_philo)
// {
// 	t_philo		*ph;

// 	ph = (t_philo *)catch_philo;
// 	if (ph->manager->nbr_philo == 1)
// 		one_philo_function(ph);
// 	// if (ph->manager->nbr_philo % 2 == 0 && ph->philo_id % 2 == 1) ph->manager->nbr_philo < 25 && 
// 	// if (ph->manager->nbr_philo < 25 && ph->philo_id % 2 == 1)
// 	// 	usleep(ph->philo_id * 1000 / 2);
// 	// usleep(ph->time_to_eat * 1000 / 2);
// 	// if (ph->philo_id % 2 == 0)
// 	// 	usleep(300);
// 	// this and
// 	if (ph->philo_id % 2 == 0)
// 		usleep(500);
// 	// usleep(ph->philo_id * 500 / 2);
// 	while(!global_grim_dead_f(ph->manager) && !philo_meal_allowence(ph) && !philo_dead_f(ph))
// 	{
// 		// if (ph->philo_id % 2 == 1 && ph->manager->nbr_philo % 2 == 1)
// 		// 	usleep(ph->time_to_eat * 1000 / 2);
// 		if (ph->time_to_die - (get_local_time(ph->manager) - time_since_last_meal(ph)) >= ph->time_to_eat * 1.5)
// 		{
// 			// if (ph->philo_id % 2 == 1)
// 			printf("%d take a pause\n", ph->philo_id);
// 			ft_sleep(ph->time_to_eat, ph);
// 			// else
// 			// 	usleep(100);
// 		}
// 		take_fork(ph);
// 		if (exit_thread(ph))
// 			return (NULL);
// 		philo_eat(ph);
// 		if (exit_thread(ph))
// 			return (NULL);
// 		philo_sleep(ph);
// 		if (exit_thread(ph))
// 			return (NULL);
// 		philo_think(ph);
// 		if (exit_thread(ph))
// 			return (NULL);
// 		// if (get_local_time(ph->manager) > ph->time_to_die * 1.5)
// 	}
// 	return (NULL);
// }