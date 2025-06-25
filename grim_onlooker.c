/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_onlooker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:47:22 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/25 13:49:03 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	grim_print_messages(t_manager *m, int num, char *str)
{
	if (chekc_if_philo_dead(m))
		return ;
	pthread_mutex_lock(&m->printf);
	printf("%ld %d %s\n", get_local_time(m), num, str);
	pthread_mutex_unlock(&m->printf);
}

int	chekc_if_philo_dead(t_manager *grim)
{
	pthread_mutex_lock(&grim->grim_mutex);
	if (grim->dead == 1)
	{
		pthread_mutex_unlock(&grim->grim_mutex);
		return (1);
	}
	pthread_mutex_unlock(&grim->grim_mutex);
	return (0);
}

void	raise_philo_dead_flag(t_philo *p)
{
	pthread_mutex_lock(&p->personal_mutex);
	p->phil_dead = 1;
	pthread_mutex_unlock(&p->personal_mutex);
}

int	meal_allowence_grim_check(t_manager *grim)
{
	// printf("------------> here\n");
	pthread_mutex_lock(&grim->grim_mutex);
	if (grim->num_of_meals != 0 && (grim->num_of_meals == grim->finished_meals_by_all))
	{
		// grim->dead = 1;
		// grim_print_messages(grim, 500, "all meals finished: ");
		pthread_mutex_lock(&grim->printf);
		printf("%ld all meals finished: %d\n", get_time() - grim->start_time, \
													grim->finished_meals_by_all);
		pthread_mutex_unlock(&grim->printf);
		pthread_mutex_unlock(&grim->grim_mutex);
		return (0);
	}
	pthread_mutex_unlock(&grim->grim_mutex);
	return (1);
}

void	terminalte(t_manager *grim, int i)
{
	pthread_mutex_lock(&grim->grim_mutex);
	grim->dead = 1;
	pthread_mutex_unlock(&grim->grim_mutex);
	// grim_print_messages(grim, i + 1, "dead");
	pthread_mutex_lock(&grim->printf);
	printf("%ld %d dead\n", get_time() - grim->start_time, i + 1);
	pthread_mutex_unlock(&grim->printf);
	killer_funcion(grim);
	raise_philo_dead_flag(&grim->arr_of_philos[i]);
}

void	*grim_onlooker(void *manager)
{
	t_manager	*grim;
	int			i;

	i = 0;
	grim = (t_manager *)manager;
	while (!global_grim_dead_f(grim))
	{
		i = 0;
		while (i < grim->nbr_philo)
		{
			// if (!meal_allowence_grim_check(grim))
			// 	return (NULL);
			if (meal_allowence_grim_check(grim) && \
				time_since_last_meal(&grim->arr_of_philos[i]) > \
				grim->time_to_die)
			{
				terminalte(grim, i);
				break ;
			}
			i++;
		}
		usleep(100);
	}
	return (NULL);
}
