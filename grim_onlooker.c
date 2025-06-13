/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_onlooker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:47:22 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/13 18:24:51 by penchoivano      ###   ########.fr       */
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
	while (!global_grim_dead_f(grim))
	{
		i = 0;
		while (i < grim->nbr_philo)
		{
			if (time_since_last_meal(&grim->arr_of_philos[i]) > grim->time_to_die)
			{
				pthread_mutex_lock(&grim->printf);
				grim->dead = 1;
				printf("grim_onlooker: philo %d dead ==> time: %ld\n", i, get_time() - grim->start_time);
				pthread_mutex_unlock(&grim->printf);
				raise_philo_dead_flag(&grim->arr_of_philos[i]);
				break ;
			}
			// check the meal allowences of all philos
			// if ()
			i++;
		}
		if (global_grim_dead_f(grim) == 1)
		{
			killer_funcion(grim);
			return (NULL);
		}
		usleep(500); // sleep for a short time to avoid busy waiting
	}

	return (NULL);
	// pthread_mutex_lock(&grim->printf);
	// printf("grim -> philo %d dead> :%d\n",i ,grim->arr_of_philos[i].phil_dead);
	// pthread_mutex_unlock(&grim->printf);
}
// pthread_mutex_lock(&grim->printf);
// printf("time_since_last_meal: %ld grim->time_to_die: %d\n", time_since_last_meal(&grim->arr_of_philos[i]), grim->time_to_die);
// pthread_mutex_unlock(&grim->printf);

	// pthread_mutex_lock(&grim->printf);
	// printf("\n\nhello from the grim -> %d\n", grim->nbr_philo);
	// pthread_mutex_unlock(&grim->printf);
// int	is_all_dead(t_manager *m)
// {
// 	int	dead;

// 	dead = 0;
// 	pthread_mutex_lock(&m->grim_mutex);
// 	dead = m->dead;
// 	pthread_mutex_unlock(&m->grim_mutex);
// 	return (dead);
// }

// int	is_philo_dead(t_philo *philo)
// {
// 	int	info;

// 	pthread_mutex_lock(&philo->personal_mutex);
// 	info =  philo->phil_dead;
// 	pthread_mutex_unlock(&philo->personal_mutex);
// 	return (info);
// }
