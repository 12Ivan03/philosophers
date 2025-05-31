/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:50:57 by ipavlov           #+#    #+#             */
/*   Updated: 2025/02/25 22:14:52 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int	init_mutex(t_manager *manager)
{
	pthread_mutex_t	*arr_forks;
	int				i;

	arr_forks = (pthread_mutex_t *)malloc(manager->nbr_philo * sizeof(pthread_mutex_t));
	if (arr_forks == NULL)
		return (0);
	i = 0;
	while (i < manager->nbr_philo)
	{
		if (pthread_mutex_init(&arr_forks[i], NULL) != 0)
		{
			while (i >= 0)
			{
				pthread_mutex_destroy(&arr_forks[i]);
				i--;
			}
			free(arr_forks);
			return (0);
		}
		i++;
	}
	manager->forks = arr_forks;
	pthread_mutex_init(&manager->printf, NULL);
	return (1);
}
