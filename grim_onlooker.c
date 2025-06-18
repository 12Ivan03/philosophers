/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_onlooker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:47:22 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/18 14:38:58 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	raise_philo_dead_flag(t_philo *p)
{
	pthread_mutex_lock(&p->personal_mutex);
	p->phil_dead = 1;
	pthread_mutex_unlock(&p->personal_mutex);
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
	return (0);
}

int meal_allowence_grim_check(t_manager *grim)
{
	pthread_mutex_lock(&grim->grim_mutex);
	if (grim->num_of_meals == grim->finished_meals_by_all)
	{
		pthread_mutex_unlock(&grim->grim_mutex);
		return (0);
	}
	pthread_mutex_unlock(&grim->grim_mutex);
	return (1);
}

void *grim_onlooker(void *manager)
{
	t_manager	*grim;
	int			i;

	i = 0;
	grim = (t_manager *)manager;
	while (!global_grim_dead_f(grim) && meal_allowence_grim_check(grim))
	{
		i = 0;
		while (i < grim->nbr_philo)
		{
			if (time_since_last_meal(&grim->arr_of_philos[i]) > grim->time_to_die)
			{
				pthread_mutex_lock(&grim->printf);
				printf("%ld %d dead\n", get_time() - grim->start_time, i + 1);
				pthread_mutex_unlock(&grim->printf);
				pthread_mutex_lock(&grim->grim_mutex);
				grim->dead = 1;
				pthread_mutex_unlock(&grim->grim_mutex);
				raise_philo_dead_flag(&grim->arr_of_philos[i]);
				break ;
			}
			i++;
		}
		if (global_grim_dead_f(grim))//) == 1)
			return (killer_funcion(grim), NULL);
		usleep(100);
	}
	return (NULL);
}
