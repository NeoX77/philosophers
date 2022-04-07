#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int				toto = 0;
pthread_mutex_t	mutex;

void*	routine()
{
	sleep(1);
	pthread_mutex_lock(&mutex);
	for (int i = 0; i < 1000000; i++)
		toto++;
	pthread_mutex_unlock(&mutex);
}

int	main(void)
{
	pthread_t	threads[5];

	pthread_mutex_init(&mutex, NULL);
	for (int i = 0; i < 5; i++)
	{
		if (pthread_create(&threads[i], NULL, &routine, NULL) != 0)
			return (1);
		printf("Thread [%i] has started\n", i);
	}
	for (int i = 0; i < 5; i++)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (1);
		printf("Thread [%i] has finished\n", i);
	}
	pthread_mutex_destroy(&mutex);
	printf("%i\n", toto);
	return (0);
}
