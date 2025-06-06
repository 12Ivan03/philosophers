/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:08:32 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/06 19:42:34 by penchoivano      ###   ########.fr       */
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
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				num_of_meals;
	int				phil_dead;
	time_t			time_from_last_meal;
	pthread_mutex_t	personal_mutex;
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
	int				finished_meals_by_all;
	int				dead;
	time_t			start_time;
	t_philo			*arr_of_philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printf;
	pthread_mutex_t	grim_mutex;
	pthread_t		grim_onlooker;
	pthread_t		*ptr_to_bodies;
}	t_manager;

int				check_argv(int argc,char *argv[]);
int				declaration_manager(t_manager *manager, int argc, char *argv[]);
int				declaration_philosophers(t_manager *manager);
int				create_threads(t_manager *manager);
int				init_mutex(t_manager *manager);
void			*routine(void *philo);
void			*grim_onlooker(void *manager);
int				join_threads(t_manager *manager);

// lib functions
int				ft_atol(const char *nptr);
int				ft_isdigit(char *argv);
time_t			get_time();

// cleaner functions
void			clean_mutex_forks(pthread_mutex_t *arr, int i);
void			clean_helper(pthread_mutex_t *arr, int i, t_manager *manager);
void			clear_personal_mutexes(t_manager *manager, int i);
void			clean_personal_threads(pthread_t *bodies, int *i);

// error handler
void			printf_error(int i);

// routine helper functions
int				philo_meal_allowence(t_philo *philo);
void			printf_forks(t_philo *philo);

// get info functions
int				global_grim_dead_f(t_manager *manager);
int				philo_dead_f(t_philo *philo);
time_t			 get_time_to_eat(t_philo *philo);

#endif
