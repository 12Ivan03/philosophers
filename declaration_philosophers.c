/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:04:33 by ipavlov           #+#    #+#             */
/*   Updated: 2025/02/25 22:32:08 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	init_philo(t_philo *arr_philo, t_manager *manager, int i)
{
	arr_philo->philo_id = i + 1;
	arr_philo->time_to_die = manager->time_to_die;
	arr_philo->time_to_eat = manager->time_to_eat;
	arr_philo->time_to_sleep = manager->time_to_sleep;
	arr_philo->num_of_meals = manager->num_of_meals;
	arr_philo->phil_dead = manager->dead;
	arr_philo->time_from_last_meal =  0;//maybe set the current time?
	arr_philo->left_f = &manager->forks[i];
	arr_philo->right_f = &manager->forks[(i + 1) % manager->nbr_philo];
	arr_philo->manager = manager;
}

int	declaration_philosophers(t_manager *manager)
{
	t_philo	*arr_philo;
	int		i;

	arr_philo = (t_philo *)malloc(manager->nbr_philo * sizeof(t_philo));
	if (arr_philo == NULL)
		return (0);
	i = 0;
	while (i < manager->nbr_philo)
	{
		init_philo(&arr_philo[i], manager, i);
		i++;
	}
	manager->arr_of_philos = arr_philo;
	return (1);
}

// // printf the created array of philos
// i = 0;
// while (i < manager->nbr_philo)
// {
// 	printf("\n\nCREATED PHILOS\n");
// 	printf("philo id: %d\n",arr_philo[i].philo_id);
// 	printf("philo die: %d\n",arr_philo[i].time_to_die);
// 	printf("philo eat: %d\n",arr_philo[i].time_to_eat);
// 	printf("philo sleep: %d\n",arr_philo[i].time_to_sleep);
// 	printf("philo num of meals: %d\n",arr_philo[i].num_of_meals);
// 	printf("philo dead: %d\n",arr_philo[i].phil_dead);
// 	printf("philo time from last meal: %d\n",arr_philo[i].time_from_last_meal);
// 	printf("philo manager number of philos: %d\n\n",arr_philo[i].manager->nbr_philo);
// 	i++;
// }
