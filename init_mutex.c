/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:50:57 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/06 19:19:10 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	init_mutex(t_manager *manager)
{
	pthread_mutex_t	*arr_forks;
	int				i;

	arr_forks = (pthread_mutex_t *)malloc(manager->nbr_philo \
					* sizeof(pthread_mutex_t));
	if (arr_forks == NULL)
		return (0);
	i = 0;
	while (i < manager->nbr_philo)
	{
		if (pthread_mutex_init(&arr_forks[i], NULL) != 0)
			return (clean_mutex_forks(arr_forks, i), 0);
		i++;
	}
	manager->forks = arr_forks;
	if (pthread_mutex_init(&manager->printf, NULL) != 0)
		return (clean_helper(arr_forks, i, manager), 0);
	if (pthread_mutex_init(&manager->grim_mutex, NULL) != 0)
		return (clean_helper(arr_forks, i, manager), 0);
	return (1);
}
