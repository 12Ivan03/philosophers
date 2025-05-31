
#include "./philosophers.h"

void *routine(void *catch_philo)
{
	t_philo *philo;

	philo = (t_philo *)catch_philo;
	pthread_mutex_lock(&philo->manager->printf);
	printf("philo Id: %d\n",philo->philo_id);
	pthread_mutex_unlock(&philo->manager->printf);
	return NULL;
}
