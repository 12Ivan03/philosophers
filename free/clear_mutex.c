
#include <philosophers.h>

void	clean_mutex_forks(pthread_mutex_t *arr, int i)
{
	// i--; // ?
	while (i >= 0)
	{
		pthread_mutex_destroy(&arr[i]);
		i--;
	}
	free(arr);
	arr = NULL;
	// printf_error(2);
}

void	clean_helper(pthread_mutex_t *arr, int i, t_manager *manager)
{
	pthread_mutex_destroy(&manager->printf);
	clean_mutex_forks(arr, i);
}

void	clean_full_manager(pthread_mutex_t *arr, int i, t_manager *manager)
{
	pthread_mutex_destroy(&manager->grim_mutex);
	clean_helper(arr, i, manager);
}

void	clear_personal_mutexes(t_manager *manager, int i)
{
	t_philo *philo;

	philo = manager->arr_of_philos;
	while(i >= 0)
	{
		pthread_mutex_destroy(&philo[i].personal_mutex);
		i--;
	}
	clean_full_manager(manager->forks, manager->nbr_philo - 1, manager);
	if (manager->arr_of_philos)
	{
		free(manager->arr_of_philos);
		manager->arr_of_philos = NULL;
	}
}

void	clear_manager_and_philos(t_manager *manager)
{
	clear_personal_mutexes(manager, manager->nbr_philo - 1);
	if (manager->arr_of_philos)
	{
		free(manager->arr_of_philos);
		manager->arr_of_philos = NULL;
	}
	if (manager->ptr_to_bodies)
	{
		free(manager->ptr_to_bodies);
		manager->ptr_to_bodies = NULL;
	}
}
// threads

void	clean_personal_threads(t_manager *manager, pthread_t *bodies, int *i)
{
	while ((*i) >= 0)
	{
		pthread_join(bodies[(*i)], NULL);
		(*i)--;
	}
	if (bodies)
	{
		free(bodies);
		bodies = NULL;
	}
	clear_manager_and_philos(manager);
}

void	free_all(t_manager *manager)
{
	int i;

	i = 0;
	if (manager->ptr_to_bodies)
	{
		while(i < manager->nbr_philo)
		{
			pthread_join(manager->ptr_to_bodies[i], NULL);
			i++;
		}
		free(manager->ptr_to_bodies);
		manager->ptr_to_bodies = NULL;
	}
	pthread_join(manager->grim_onlooker, NULL);
	clear_manager_and_philos(manager);
}
