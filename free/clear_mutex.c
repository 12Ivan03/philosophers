
#include <philosophers.h>

void	clean_mutex_forks(pthread_mutex_t *arr, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&arr[i]);
		i--;
	}
	free(arr);
	printf_error(2);
}

void	clean_helper(pthread_mutex_t *arr, int i, t_manager *manager)
{
	clean_mutex_forks(arr, i);
	pthread_mutex_destroy(&manager->printf);
	printf_error(2);
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
	clean_helper(manager->forks, manager->nbr_philo - 1, manager);
}

void	clean_personal_threads(pthread_t *bodies, int *i)
{
	while ((*i) >= 0)
	{
		pthread_join(bodies[(*i)], NULL);
		(*i)--;
	}
	free(bodies);
	// clean manager.
	printf("Error creating threads\n");
}
