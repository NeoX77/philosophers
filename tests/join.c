#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

void*	roll()
{
	int	value = (rand() % 6) + 1;
	int	*buffer = malloc(sizeof(int));

	*buffer = value;
	return ((void *)buffer);
}

int	main(void)
{
	int			*toto;
	pthread_t	thread;

	srand(time(NULL));
	if (pthread_create(&thread, NULL, &roll, NULL) != 0)
		return (1);
	if (pthread_join(thread, (void **)&toto) != 0)
		return (1);
	printf("%i\n", *toto);
	free(toto);
	return (0);
}
