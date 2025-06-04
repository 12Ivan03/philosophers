/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:05:05 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/04 14:49:28 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	main(int argc, char *argv[])
{
	t_manager manager;

	// printf("1\n");
	if (!check_argv(argc, argv))
		return (1);
	// printf("2\n");
	if (!declaration_manager(&manager, argc, argv))
		return (1);
	// printf("3\n");
	if (!init_mutex(&manager))
		return (1);
	// printf("4\n");
	if (!declaration_philosophers(&manager))
		return (1);
	// printf("5\n");
	if (!create_threads(&manager))
		return (1);
	// printf("6\n");
	join_threads(&manager);
	// free the manager shit things inside.

	// printf the created array of philos
	int i = 0;
	while (i < manager.nbr_philo)
	{
		printf("\n\nCREATED PHILOS\n");
		printf("philo id: %d\n",manager.arr_of_philos[i].philo_id);
		printf("philo die: %d\n",manager.arr_of_philos[i].time_to_die);
		printf("philo eat: %d\n",manager.arr_of_philos[i].time_to_eat);
		printf("philo sleep: %d\n",manager.arr_of_philos[i].time_to_sleep);
		printf("philo num of meals: %d\n",manager.arr_of_philos[i].num_of_meals);
		printf("philo dead: %d\n",manager.arr_of_philos[i].phil_dead);
		printf("philo time from last meal: %d\n",manager.arr_of_philos[i].time_from_last_meal);
		printf("philo manager number of philos: %d\n\n",manager.arr_of_philos[i].manager->nbr_philo);
		// printf("philo id: %p\n",manager.arr_of_philos[i].left_f);
		// printf("philo die: %p\n",manager.arr_of_philos[i].right_f);
		// printf("philo eat: %d\n",manager.arr_of_philos[i].time_to_eat);
		// printf("philo sleep: %d\n",manager.arr_of_philos[i].time_to_sleep);
		i++;
	}
	// check the info correctness...
	printf("manager nbr of philosophers: %d\n", manager.nbr_philo);
	printf("manager time to die: %d\n", manager.time_to_die);
	printf("manager time to eat: %d\n", manager.time_to_eat);
	printf("manager time to sleep: %d\n", manager.time_to_sleep);
	printf("manager num of meals: %d\n", manager.num_of_meals);
	printf("manager dead philosophers: %d\n", manager.dead);
	return (0);
}
