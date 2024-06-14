/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreamerlino <andreamerlino@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:27:17 by andreamerli       #+#    #+#             */
/*   Updated: 2024/06/14 22:28:56 by andreamerli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdint.h>

typedef struct s_general
{
	int				g[5];
	int				i;
	pthread_t		*philosophers;
	pthread_t		monitor;
	pthread_t		monitor2;
	pthread_mutex_t	*mutex_forks;
	pthread_mutex_t	*mutex_eat;
	u_int64_t		start;
	int				eat_times;
	int				dead;
	int				should_break;
}	t_general;

typedef struct s_thread_data
{
	t_general		*general;
	int				number_p;
	int				eat;
	u_int64_t		last_meal;

}	t_thread_data;

size_t		ft_strlen(const char *s);
int			checker(t_general *g, char **argv, int argc);
void		set_philo(t_general *g, t_thread_data *data, int argc);
void		set_threads(t_general *g, t_thread_data *data, int argc);
void		destroy_free(t_general *g, t_thread_data *data);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_usleep(size_t milliseconds);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
int			string_checker(char **argv);
u_int64_t	get_time(void);

void		*monitor(void *args);
void		*monitor2(void *args);
void		*routine(void *arg);
#endif
