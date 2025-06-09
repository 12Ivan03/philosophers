/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_onlooker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:47:22 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/09 11:17:13 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	is_all_dead(t_manager *m)
{
	int	dead;

	dead = 0;
	pthread_mutex_lock(&m->grim_mutex);
	dead = m->dead;
	pthread_mutex_unlock(&m->grim_mutex);
	return (dead);
}

int	killer_funcion(t_manager *grim)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&grim->grim_mutex);
	if (grim->dead != 0)
		grim->dead = 1;
	pthread_mutex_unlock(&grim->grim_mutex);
	while (i < grim->nbr_philo)
	{
		pthread_mutex_lock(&grim->arr_of_philos[i].personal_mutex);
		if (grim->arr_of_philos[i].phil_dead != 1)
			grim->arr_of_philos[i].phil_dead = 1;
		pthread_mutex_unlock(&grim->arr_of_philos[i].personal_mutex);
		i++;
		if (i >= grim->nbr_philo)
			break ;
	}
	pthread_mutex_lock(&grim->printf);
	printf("grim_onlooker: all philos killed\n");
	pthread_mutex_unlock(&grim->printf);
	return (0);
}

void *grim_onlooker(void *manager)
{
	t_manager	*grim;
	int			i;

	i = 0;
	grim = (t_manager *)manager;
	// int j = 0;
	// while (i < grim->nbr_philo)
	while (!is_all_dead(grim))// && j < 10) //or while (grim->dead != 1)
	{
		// check if any of the phios are dead - in a loop
		i = 0;
		while (i < grim->nbr_philo)// && i < 10)
		{
			// pthread_mutex_lock(&grim->printf);
			// printf("tiem since last meal checked%d\n",time_since_last_meal(&grim->arr_of_philos[i]) > grim->time_to_die);
			// pthread_mutex_unlock(&grim->printf);

			if (time_since_last_meal(&grim->arr_of_philos[i]) > grim->time_to_die)
			{
				pthread_mutex_lock(&grim->printf);
				grim->dead = 1;
				printf("grim_onlooker: philo %d dead\n", i);
				pthread_mutex_unlock(&grim->printf);
				raise_philo_dead_flag(&grim->arr_of_philos[i]);
				break ;
			}
			i++;
		}
		if (is_all_dead(grim) == 1)
		{
			killer_funcion(grim);
			return (NULL);
		}
		// j++;
		usleep(1000); // sleep for a short time to avoid busy waiting
	}

	return (NULL);
	// pthread_mutex_lock(&grim->printf);
	// printf("grim -> philo %d dead> :%d\n",i ,grim->arr_of_philos[i].phil_dead);
	// pthread_mutex_unlock(&grim->printf);
}

	// pthread_mutex_lock(&grim->printf);
	// printf("\n\nhello from the grim -> %d\n", grim->nbr_philo);
	// pthread_mutex_unlock(&grim->printf);
