/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declaration_philosophers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:04:33 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/04 14:01:17 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	init_philo(t_philo *arr_philo, t_manager *manager, int i)
{
	arr_philo->philo_id = i + 1;
	arr_philo->time_to_die = manager->time_to_die;
	arr_philo->time_to_eat = manager->time_to_eat;
	arr_philo->time_to_sleep = manager->time_to_sleep;
	arr_philo->num_of_meals = manager->num_of_meals;
	arr_philo->phil_dead = manager->dead;
	arr_philo->time_from_last_meal =  get_time();
	arr_philo->left_f = &manager->forks[i];
	arr_philo->right_f = &manager->forks[(i + 1) % manager->nbr_philo];
	arr_philo->manager = manager;
}

void	clear_personal_threads(t_manager *manager, int i)
{
	t_philo *philo;

	philo = manager->arr_of_philos;
	while(i >= 0)
	{
		pthread_mutex_destroy(&philo[i].personal_mutex);
		i--;
	}
	clean_helper(manager->forks, manager->nbr_philo - 1, manager);
}

int	init_personal_mutex_in_philo(t_manager *manager)
{
	int i;

	i = 0;
	// printf("4.3.1\n");
	while(i < manager->nbr_philo)
	{
		if (pthread_mutex_init(&manager->arr_of_philos[i].personal_mutex, NULL) != 0)
		{
			// printf("4.3.1 - %d\n", i);
			clear_personal_threads(manager, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	declaration_philosophers(t_manager *manager)
{
	t_philo	*arr_philo;
	int		i;
	// printf("4.1\n");
	arr_philo = (t_philo *)malloc(manager->nbr_philo * sizeof(t_philo));
	if (arr_philo == NULL)
	{
		printf_error(3);
		return (0);
	}
	// printf("4.2\n");
	i = 0;
	while (i < manager->nbr_philo)
	{
		init_philo(&arr_philo[i], manager, i);
		i++;
	}
	// printf("4.3\n");
	manager->arr_of_philos = arr_philo;
	if (init_personal_mutex_in_philo(manager))
		return (0);
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
