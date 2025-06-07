
#include <philosophers.h>

void	raise_philo_dead_flag(t_philo *p)
{
	pthread_mutex_lock(&p->personal_mutex);
	p->phil_dead = 1;
	pthread_mutex_unlock(&p->personal_mutex);
}
