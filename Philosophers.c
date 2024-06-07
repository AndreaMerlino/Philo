#include "Philosophers.h"

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(100);
	return (0);
}

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

void *monitor2(void *args)
{
	t_thread_data *data = (t_thread_data*)args;
	t_general *g = data->general;
	int i;
	while(g->eat_times > 0)
	{
		i = 0;
		while (i < g->g[0])
		{
			if(i == 0)
				g->eat_times = 0;
			g->eat_times += data[i].eat;
			i ++;
		}
		 usleep(1000);
	}
	return (NULL);
}
void *monitor(void *args) {
   t_thread_data *data = (t_thread_data*)args;
t_general *g = data->general;
   int i;
   int should_break = 0;
    while (1) {
		i = 0;
		while( i < g->g[0])
     {

		if ((get_time() - data[i].last_meal) > (uint64_t) (g->g[1]))
			{

				should_break = 1;
				 g->dead = 1;
				printf("%llu %d died\n", get_time() - g->start,  data[i].number_p + 1);
				break;
			}
			if(g->eat_times < 1)
				{
					should_break = 1;
					break;
				}
			i++;

        }
		if (should_break > 0)
			break;
        usleep(1000);
    }
	return (NULL);
}

void* routine(void *arg) {

	 t_thread_data *data = (t_thread_data*)arg;
    t_general *g = data->general;

	while( g->eat_times > 0 || data->eat > 0)
	{
	if(data->number_p % 2 == 0)
	    pthread_mutex_lock(&g->mutex_forks[data->number_p ]);
	else
	{
		if (data->number_p == (g->g[0] - 1))
			pthread_mutex_lock(&g->mutex_forks[0]);
		else
			pthread_mutex_lock(&g->mutex_forks[data->number_p  + 1]);

	}
	if (g->dead)
            break;
	printf("%llu %d has taken a fork\n", get_time() - g->start,  data->number_p + 1);
	if(data->number_p % 2 == 0)
	{
		 if (data->number_p == (g->g[0] - 1))
		 pthread_mutex_lock(&g->mutex_forks[0]);
		else
		 pthread_mutex_lock(&g->mutex_forks[data->number_p + 1]);
	}
	else
		pthread_mutex_lock(&g->mutex_forks[data->number_p ]);
		if (g->dead)
            break;
	printf("%llu %d has taken a fork\n", get_time() - g->start,  data->number_p + 1);

	data->last_meal = get_time();

	printf("%llu %d is eating \n",get_time() - g->start,  data->number_p + 1);
if (g->dead)
            break;
	ft_usleep(g->g[2]);

	if(data->number_p  % 2 == 0)
		pthread_mutex_unlock(&g->mutex_forks[data->number_p ]);

	else
	{
		if (data->number_p  == (g->g[0] - 1))
			pthread_mutex_unlock(&g->mutex_forks[0]);
		else
			pthread_mutex_unlock(&g->mutex_forks[data->number_p  + 1]);
	}
	if(data->number_p  % 2 == 0)
	{
		if (data->number_p == (g->g[0] - 1))
			pthread_mutex_unlock(&g->mutex_forks[0]);
		else
			pthread_mutex_unlock(&g->mutex_forks[data->number_p + 1]);
	}
	else
	pthread_mutex_unlock(&g->mutex_forks[data->number_p ]);
	if (g->dead)
            break;
    printf("%llu %d is sleeping \n",get_time() - g->start,  data->number_p + 1);
	ft_usleep(g->g[3]);
	if (g->dead)
            break;
	printf("%llu %d is thinking \n",get_time() - g->start,  data->number_p + 1);
	data->eat -= 1;
	usleep(100);
}
return (NULL);
}

int main (int argc, char ** argv)
{
	t_general	g;
	t_thread_data *data;

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
		g.philosophers = ft_calloc(sizeof(pthread_t) * g.g[0], 1);
		g.mutex_forks = ft_calloc(sizeof(pthread_mutex_t) * g.g[0], 1);
		g.start = get_time();
		g.dead = 0;
		g.eat_times =1;
		while(g.i < g.g[0])
		{
			if(pthread_mutex_init(&g.mutex_forks[g.i] , NULL) != 0)
				return(2);
			g.i ++;
		}
		g.i = 0;

		data = ft_calloc(sizeof(t_thread_data ) * g.g[0], 1);
		g.i = 0;
		while (g.i < g.g[0])
		{
        data[g.i].general = &g;
        data[g.i].number_p = g.i;
		data[g.i].eat = (argc == 6) ? g.g[4] : 2147483647;
		data[g.i].last_meal = g.start;
		g.i ++;
		}
		g.i = 0;
		if(argc == 6)
			pthread_create(&g.monitor2, NULL, monitor2, data);
		pthread_create(&g.monitor, NULL, monitor, data);

		while (g.i < g.g[0])
		{
			printf("the size of philosopher %d is %lu and data is %lu \n",g.i +1,  sizeof(g.philosophers[g.i]),sizeof(data[g.i]) );
			if( pthread_create(&g.philosophers[g.i], NULL, routine, &data[g.i]) != 0)
				return (1);
			g.i ++;
		}
		if(argc == 6)
		pthread_join(g.monitor2, NULL);
		 pthread_join(g.monitor, NULL);

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
		free(data);
		free(g.philosophers);
		free(g.mutex_forks);
}
