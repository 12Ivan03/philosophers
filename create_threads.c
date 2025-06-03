/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:47:40 by ipavlov           #+#    #+#             */
/*   Updated: 2025/02/28 16:34:07 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	clean_create(pthread_t *bodies, int *i)
{
	while ((*i) >= 0)
	{
		pthread_join(bodies[(*i)], NULL);
		(*i)--;
	}
	free(bodies);
	printf("Error creating threads\n");
}

int	create_threads(t_manager *manager)
{
	pthread_t	*bodies;
	int			i;
	int			n;

	n = manager->nbr_philo;
	bodies = (pthread_t *)malloc(n * sizeof(pthread_t));
	i = 0;
	while (i < n)
	{
		if (pthread_create(&bodies[i], NULL, routine, \
			&manager->arr_of_philos[i]) != 0)
		{
			clean_create(bodies, &i);
			return (0);
		}
		i++;
	}
	if (pthread_create(&manager->grim_onlooker, NULL, grim_onlooker, manager) != 0)
	{
		clean_create(bodies, &i);
		pthread_join(manager->grim_onlooker, NULL);
		return (0);
	}
	manager->ptr_to_bodies = bodies;
	return (1);
}
