#include <stdio.h>
#include <pthread.h>

int				toto = 0;
pthread_mutex_t	mutex;

void*	routine()
{
	int	i;

	pthread_mutex_lock(&mutex);
	i = 0;
	while (i++ < 100000)
		toto++;
	pthread_mutex_unlock(&mutex);
}

int	main(void)
{
	pthread_t	thread0, thread1;

	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&thread0, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&thread1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_join(thread0, NULL) != 0)
		return (1);
	if (pthread_join(thread1, NULL) != 0)
		return (1);
	pthread_mutex_destroy(&mutex);
	printf("%i\n", toto);
	return (0);
}
