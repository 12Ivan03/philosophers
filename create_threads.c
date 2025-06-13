/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:47:40 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/13 16:30:02 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	create_threads(t_manager *manager)
{
	pthread_t	*bodies;
	int			i;
	int			n;

	n = manager->nbr_philo;
	bodies = (pthread_t *)malloc(n * sizeof(pthread_t));
	if (bodies == NULL)
		return (clear_manager_and_philos(manager) ,0);
	i = 0;
	while (i < n)
	{
		if (pthread_create(&bodies[i], NULL, &routine, \
			&manager->arr_of_philos[i]) != 0)
			return (clean_personal_threads(manager, bodies, &i), 0);
		i++;
	}
	if (pthread_create(&manager->grim_onlooker, NULL, \
		&grim_onlooker, manager) != 0)
		return (clean_personal_threads(manager, bodies, &i), 0);
	manager->ptr_to_bodies = bodies;
	return (1);
}
