
#include <philosophers.h>

void	printf_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->manager->printf);
	// printf("philo ID: %d: start time: %ld\n",  philo->philo_id, philo->manager->start_time);
	// printf("philo ID: %d: fork right address: %p\n",  philo->philo_id, philo->right_f);
	// printf("philo ID: %d: fork left address: %p\n",  philo->philo_id, philo->left_f);
	printf("philo ID: %d: has taken both forks: %ld\n",  philo->philo_id, get_time());
	pthread_mutex_unlock(&philo->manager->printf);
}

int	philo_meal_allowence(t_philo *philo)
{
	if (philo->manager->num_of_meals > 0 && \
		philo->num_of_meals >= philo->manager->num_of_meals)
	{
		pthread_mutex_lock(&philo->personal_mutex);
		philo->phil_dead = 1;
		pthread_mutex_unlock(&philo->personal_mutex);
		pthread_mutex_lock(&philo->manager->printf);
		printf("philo ID: %d: has finished eating\n", philo->philo_id);
		pthread_mutex_unlock(&philo->manager->printf);
		return (1);
	}
	return (0);
}
