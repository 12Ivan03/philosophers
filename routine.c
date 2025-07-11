/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:47:31 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/25 15:08:12 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	gorge_oneself(t_philo *ph)
{
	take_fork(ph);
	philo_eat(ph);
	philo_sleep(ph);
	philo_think(ph);
	return (0);
}

void	staggering_meassures(t_philo *ph)
{
	if (ph->manager->nbr_philo % 2 == 1 && ph->manager->nbr_philo < 51 \
											&& ph->philo_id % 2 == 1)
		usleep(ph->time_to_eat * 1000 / 2);
	else if (ph->manager->nbr_philo % 2 == 1 && ph->philo_id % 2 == 1)
		usleep(400);
	if (ph->manager->nbr_philo % 2 == 0 && ph->manager->nbr_philo >= 50 \
										&& ph->philo_id % 2 == 1)
		usleep(200);
	else if (ph->manager->nbr_philo % 2 == 0 && ph->manager->nbr_philo < 50 \
											&& ph->philo_id % 2 == 1)
		usleep(100);
}

void	*routine(void *catch_philo)
{
	t_philo		*ph;

	ph = (t_philo *)catch_philo;
	if (ph->manager->nbr_philo == 1)
		one_philo_function(ph);
	if (ph->manager->nbr_philo % 2 == 1 && ph->philo_id % 2 == 1)
		usleep(ph->philo_id * 1000 / 2);
	while (!global_grim_dead_f(ph->manager) && \
			!philo_meal_allowence(ph) && !philo_dead_f(ph))
	{
		staggering_meassures(ph);
		gorge_oneself(ph);
	}
	return (NULL);
}
