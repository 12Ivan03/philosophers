/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:08:32 by ipavlov           #+#    #+#             */
/*   Updated: 2025/02/28 17:44:52 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_manager t_manager;
typedef struct s_philo t_philo;

typedef struct s_philo
{
	int				philo_id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	int				phil_dead;
	int				time_from_last_meal;// from the end of their meal.
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	t_manager		*manager;
}	t_philo;

typedef struct s_manager
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	int				dead;
	t_philo			*arr_of_philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printf;
	pthread_t		grim_onlooker;
	pthread_t		*ptr_to_bodies;
}	t_manager;

int				check_argv(int argc,char *argv[]);
int				declaration_manager(t_manager *manager, int argc, char *argv[]);
int				declaration_philosophers(t_manager *manager);
int				create_threads(t_manager *manager);
int				init_mutex(t_manager *manager);
void			*routine(void *philo);
void			*grim_onlooker();
int				ft_atol(const char *nptr);
int				ft_isdigit(char *argv);
unsigned int	get_time();
void			printf_error(int i);
int				join_threads(t_manager *manager);

#endif
