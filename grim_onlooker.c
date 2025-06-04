/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_onlooker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:47:22 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/04 14:28:44 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void *grim_onlooker(void *manager)
{
	t_manager *grim;

	grim = (t_manager *)manager;

	pthread_mutex_lock(&grim->printf);
	printf("\n\nhello from the grim -> %d\n", grim->nbr_philo);
	pthread_mutex_unlock(&grim->printf);

	int i = 0;
	while (i < grim->nbr_philo)
	{
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
