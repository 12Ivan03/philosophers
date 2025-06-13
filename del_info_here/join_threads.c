/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:18:14 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/13 17:15:07 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <philosophers.h>

// int	join_threads(t_manager *manager)
// {
// 	int i;
// 	int n;

// 	n = manager->nbr_philo;
// 	i = 0;
// 	while (i < n)
// 	{
// 		pthread_join(manager->ptr_to_bodies[i], NULL);
// 		i++;
// 	}
// 	pthread_join(manager->grim_onlooker, NULL);
// 	free(manager->ptr_to_bodies);
// 	return (0);
// }
