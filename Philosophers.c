#include "Philosophers.h"

int	string_checker(char **argv)
{
	char	*temp;
	int		i;

	i = 1;
	while (argv[i] != NULL)
	{
		temp = argv[i];
		while (*temp)
		{
			if ((*temp >= 48 && *temp <= 57))
				temp++;
			else
			{
				printf ("Error\n");
				return (24);
			}
		}
		i++;
	}
	return (1);
}

int	max_min(char **argv)
{
	int i;
	char * temp;

	i = 0;
	temp = NULL;
	while (argv[i])
	{
		temp = argv[i];
	if (((ft_strlen(temp) == 10) && (ft_strncmp(temp,"2147483647", ft_strlen(temp)) > 0))
		|| ft_strlen(temp) > 10)
	{
		printf ("Error\n");
		return (100);
	}
	i ++;
	}
	return (0);
}

void* routine(void *arg) {
	 t_thread_data *data = (t_thread_data*)arg;
    t_general *g = data->general;
    int number_p = data->number_p;
	if(number_p % 2 == 0)
	    pthread_mutex_lock(&g->mutex_forks[number_p]);
	else
	{
		if (number_p == g->g[0] - 1)
			pthread_mutex_lock(&g->mutex_forks[0]);
		else
			pthread_mutex_lock(&g->mutex_forks[number_p + 1]);

	}
	printf("%d has taken a fork\n", number_p + 1);
	if(number_p % 2 == 0)
	{
		 if (number_p == g->g[0] - 1)
		 pthread_mutex_lock(&g->mutex_forks[0]);
		else
		 pthread_mutex_lock(&g->mutex_forks[number_p + 1]);
	}
	else
		pthread_mutex_lock(&g->mutex_forks[number_p]);
	printf("%d has taken a fork\n", number_p + 1);
	printf("%d is eating \n", number_p + 1);
	usleep(g->g[2]);
	if(number_p % 2 == 0)
		pthread_mutex_unlock(&g->mutex_forks[number_p]);

	else
	{
		if (number_p == g->g[0] - 1)
			pthread_mutex_unlock(&g->mutex_forks[0]);
		else
			pthread_mutex_unlock(&g->mutex_forks[number_p + 1]);
	}
	if(number_p % 2 == 0)
	{
		if (number_p == g->g[0] - 1)
			pthread_mutex_unlock(&g->mutex_forks[0]);
		else
			pthread_mutex_unlock(&g->mutex_forks[number_p + 1]);
	}
	else
	pthread_mutex_unlock(&g->mutex_forks[number_p]);
    printf("%d Ending thread\n",number_p + 1);
	free(data);
}

int main (int argc, char ** argv)
{
	t_general	g;


	g.i = 0;
	if(argc != 6 && argc != 5)
	{
		printf ("Error\n");
		return(0);
	}
	g.g[0] = string_checker(argv);
		if( g.g[0] != 1)
			return(0);
		g.g[0] = max_min(argv);
		if( g.g[0] != 0)
			return(0);
		while (g.i < 5)
		{
			if (g.i < 4)
				g.g[g.i] = ft_atoi(argv[g.i + 1]);
			else
				if(argc == 6 && g.i == 4)
					g.g[g.i] = ft_atoi(argv[5]);
		g.i ++;
		}
		g.i = 0;
		g.philosophers = malloc(sizeof(int) * g.g[0]);
		g.mutex_forks = malloc(sizeof(pthread_mutex_t) * g.g[0]);
		while(g.i < g.g[0])
		{
			pthread_mutex_init(&g.mutex_forks[g.i] , NULL);
			g.i ++;
		}

		g.i = 0;
		while (g.i < g.g[0])
		{
			 t_thread_data *data = malloc(sizeof(t_thread_data));
        data->general = &g;
        data->number_p = g.i;
       if( pthread_create(&g.philosophers[g.i], NULL, routine, data) != 0)
	   		return (1);
		g.i ++;
		}
		g.i = 0;
		while (g.i < g.g[0])
		{
			if(pthread_join(g.philosophers[g.i], NULL) != 0)
				return(2);
			g.i ++;
		}
		g.i = 0;
		while (g.i < g.g[0])
		{
			 pthread_mutex_destroy(&g.mutex_forks[g.i]);
			g.i ++;
		}
}
