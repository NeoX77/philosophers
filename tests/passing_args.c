#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

int	primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void	*routine(void *arg)
{
	int	index = *(int*)arg;

	sleep(1);
	printf("%i ", primes[index]);
	free(arg);
}

int	main(void)
{
	int			i;
	int			*tmp;
	pthread_t	th[10];

	for (i = 0; i < 10; i++)
	{
		tmp = malloc(sizeof(int));
		*tmp = i;
		if (pthread_create(&th[i], NULL, &routine, tmp) != 0)
			printf("Failed to create thread [%i]\n", i);
	}
	for (i = 0; i < 10; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
			printf("Failed to join thread [%i]\n", i);
	}
	return (0);
}
