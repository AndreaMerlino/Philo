#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_general {
    int g[5];
    int i;
    pthread_t *philosophers;
    pthread_mutex_t *mutex_forks;
} t_general;

typedef struct s_thread_data {
    t_general *general;
    int number_p;
	pthread_mutex_t *mutex_data;
} t_thread_data;

size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
#endif
