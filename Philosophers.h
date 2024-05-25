#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_general
{
	int				g[6];
	int				i;
	pthread_t		*philosophers;
	pthread_mutex_t	*mutex_forks;
	u_int64_t		start;
} t_general;

typedef struct s_thread_data {
    t_general *general;
    int number_p;
	int eat;
} t_thread_data;

size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
u_int64_t	get_time(void);
#endif
