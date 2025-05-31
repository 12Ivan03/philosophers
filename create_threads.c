
#include "./philosophers.h"

int	create_threads(t_manager *manager)
{
	pthread_t	*bodies;
	pthread_t	manage;
	int			i;
	int			n;

	n = manager->nbr_philo;
	bodies = (pthread_t *)malloc(n * sizeof(pthread_t));
	i = 0;
	while (i < n)
	{
		pthread_create(&bodies[i], NULL, routine, &manager->arr_of_philos[i]);
		i++;
	}
	pthread_create(&manage, NULL, grim_onlooker, NULL);
	i = 0;
	while (i < n)
	{
		pthread_join(bodies[i], NULL);
		i++;
	}
	return(1);
}
