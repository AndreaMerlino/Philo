/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreamerlino <andreamerlino@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:52:25 by andreamerli       #+#    #+#             */
/*   Updated: 2024/06/14 22:27:03 by andreamerli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	set_philo(t_general *g, t_thread_data *data, int argc)
{
	g->i = 0;
	g->philosophers = ft_calloc(sizeof(pthread_t) * g->g[0], 1);
	g->mutex_forks = ft_calloc(sizeof(pthread_mutex_t) * g->g[0], 1);
	g->mutex_eat = ft_calloc(sizeof(pthread_mutex_t) * g->g[0], 1);
	g->start = get_time();
	g->dead = 0;
	g->eat_times = 1;
	while (g->i < g->g[0])
	{
		pthread_mutex_init(&g->mutex_forks[g->i], NULL);
		pthread_mutex_init(&g->mutex_eat[g->i], NULL);
		g->i ++;
	}
	g->i = 0;
	while (g->i < g->g[0])
	{
		data[g->i].general = g;
		data[g->i].number_p = g->i;
		if (argc == 6)
			data[g->i].eat = g->g[4];
		else
			data[g->i].eat = 2147483647;
		data[g->i].last_meal = g->start;
		g->i ++;
	}
}

void	set_threads(t_general *g, t_thread_data *data, int argc)
{
	g->i = 0;
	pthread_create(&g->monitor, NULL, monitor, data);
	if (argc == 6 && (g->g[0] > 1))
		pthread_create(&g->monitor2, NULL, monitor2, data);
	while (g->i < g->g[0])
	{
		pthread_create(&g->philosophers[g->i], NULL, routine, &data[g->i]);
		pthread_detach(g->philosophers[g->i]);
		g->i ++;
	}
	pthread_join(g->monitor, NULL);
	if (argc == 6 && (g->g[0] > 1))
		pthread_join(g->monitor2, NULL);
	g->i = 0;
}

void	destroy_free(t_general *g, t_thread_data *data)
{
	g->i = 0;
	while (g->i < g->g[0])
	{
		pthread_mutex_destroy(&g->mutex_forks[g->i]);
		pthread_mutex_destroy(&g->mutex_eat[g->i]);
		g->i ++;
	}
	free(data);
	free(g->philosophers);
	free(g->mutex_forks);
}
