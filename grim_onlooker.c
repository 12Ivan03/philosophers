/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_onlooker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:47:22 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/06 19:10:38 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void *grim_onlooker(void *manager)
{
	t_manager *grim;

	grim = (t_manager *)manager;

	// pthread_mutex_lock(&grim->printf);
	// printf("\n\nhello from the grim -> %d\n", grim->nbr_philo);
	// pthread_mutex_unlock(&grim->printf);

	int i = 0;
	while (i < grim->nbr_philo)
	// while (1) or while (grim->dead != 1)
	{
		if (get_time() - grim->arr_of_philos[i].time_from_last_meal > grim->arr_of_philos[i].time_to_die)
		{
			printf("last mean - current time = %ld > time to die: %ld\n", get_time() - grim->arr_of_philos[i].time_from_last_meal, grim->arr_of_philos[i].time_to_die / 100);
			pthread_mutex_lock(&grim->printf);
			
			usleep(1000); // check every 1ms
		}
		// if (grim->arr_of_philos[i].phil_dead == 1)
		// {
			pthread_mutex_lock(&grim->printf);
			printf("grim -> philo %d dead> :%d\n",i ,grim->arr_of_philos[i].phil_dead);
			pthread_mutex_unlock(&grim->printf);
			// exit (1);
		// }
		// if (i >= grim->nbr_philo)
		// 	i = 0;
		i++;
	}

	return (NULL);
}
