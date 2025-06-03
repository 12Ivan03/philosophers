#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>


// int mails = 0;
// pthread_mutex_t mutex;

// void	*routine(void *i)
// {
// 	int *j = (int *)i;

// 	while ((*j)++ < 1000000)
// 	{
// 		pthread_mutex_lock(&mutex);
// 		mails++;
// 		pthread_mutex_unlock(&mutex);
// 	}
// 	return NULL;
// }

// int main()
// {
// 	int *i;
// 	pthread_t t1, t2, t3, t4;
// 	i = 0;
// 	pthread_mutex_init(&mutex, NULL);
// 	pthread_create(&t1, NULL, &routine, (void *)i);
// 	pthread_create(&t2, NULL, &routine, (void *)i);
// 	pthread_join(t1, NULL);
// 	pthread_join(t2, NULL);
// 	pthread_join(t3, NULL);
// 	pthread_join(t4, NULL);
// 	printf("mails ==> %d\n", mails);
// 	pthread_mutex_destroy(&mutex);
// 	return (0);
// }

// void	*routine()
// {
// 	printf("Thread test\n");
// 	sleep(3);
// 	printf("thread test end\n");
// 	return NULL;
// }

// int main()
// {
// 	pthread_t t1;

// 	pthread_create(&t1, NULL, &routine, NULL);
// 	pthread_join(t1, NULL);
// 	return (0);
// }

//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//
//
//
//
//
//
// Passsing pthread struct with pthread_mutex_init
//
//
//
//
//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//

// Define a struct with a mutex and a shared variable
typedef struct {
    int value;
    pthread_mutex_t lock;
} SharedData;

// Function that modifies the shared data
void *increment(void *arg) {
    SharedData *data = (SharedData *)arg; // Cast argument to struct pointer

    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&data->lock);  // Lock mutex
        data->value++;                    // Modify shared data
        pthread_mutex_unlock(&data->lock); // Unlock mutex
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    SharedData shared = { .value = 0, .lock = PTHREAD_MUTEX_INITIALIZER };  // Struct initialization

    // Initialize the mutex (Alternative way in case struct is dynamically allocated)
    pthread_mutex_init(&shared.lock, NULL);

    // Create two threads
	// pthread_create(&t1, NULL, increment, &t_env->phil->phil_id);
    pthread_create(&t1, NULL, increment, &shared);
    pthread_create(&t2, NULL, increment, &shared);

    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Destroy the mutex
    pthread_mutex_destroy(&shared.lock);

    // Print final result
    printf("Final value: %d\n", shared.value);
    return 0;
}



// pthread_mutex_t	*mutex;
// mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nbr_ph);
// pthread_mutex_t	mutex2;
// mutex = &mutex2;
// pthread_t 


	
	// // check the info correctness...
	// printf("manager nbr of philosophers: %d\n", manager.nbr_philo);
	// printf("manager time to die: %d\n", manager.time_to_die);
	// printf("manager time to eat: %d\n", manager.time_to_eat);
	// printf("manager time to sleep: %d\n", manager.time_to_sleep);
	// printf("manager num of meals: %d\n", manager.num_of_meals);
	// printf("manager dead philosophers: %d\n", manager.dead);

// phil[i].l_f = manager->forks + i;
// phil[i].r_f = manager->forks;

// {

// 	(t_manager->forks[0]);
// 	for
// }