/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:50:57 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/04 13:53:56 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	clean_threads(pthread_mutex_t *arr, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&arr[i]);
		i--;
	}
	free(arr);
	printf_error(2);
}

void	clean_helper(pthread_mutex_t *arr, int i, t_manager *manager)
{
	clean_threads(arr, i);
	pthread_mutex_destroy(&manager->printf);
	printf_error(2);
}

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
		{
			clean_threads(arr_forks, i);
			return (0);
		}
		i++;
	}
	manager->forks = arr_forks;
	if (pthread_mutex_init(&manager->printf, NULL) != 0)
	{
		clean_helper(arr_forks, i, manager);
		return (0);
	}
	return (1);
}
