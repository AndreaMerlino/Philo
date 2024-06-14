/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreamerlino <andreamerlino@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:49:08 by andreamerli       #+#    #+#             */
/*   Updated: 2024/06/14 20:49:09 by andreamerli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*monitor2(void *args)
{
	t_thread_data	*data;
	t_general		*g;
	int				i;

	data = (t_thread_data *) args;
	g = data->general;
	while (g->eat_times > 0)
	{
		i = 0;
		while (i < g->g[0])
		{
			if (i == 0)
				g->eat_times = 0;
			g->eat_times += data[i].eat;
			i ++;
		}
		if (g->dead)
			break ;
		usleep(1000);
	}
	return (NULL);
}

int	monitor_died(t_thread_data *data, t_general *g, int i)
{
	g->dead = 1;
	printf ("%llu %d died\n", get_time() - g->start, data[i].number_p + 1);
	pthread_mutex_unlock(&g->mutex_eat[i]);
	return (1);
}

void	sub_monitor(t_thread_data *data, t_general *g, int i)
{
	while (i < g->g[0])
	{
		pthread_mutex_lock(&g->mutex_eat[i]);
		usleep(500);
		if ((get_time() - data[i].last_meal) > (uint64_t)(g->g[1]))
		{
			g->should_break = monitor_died(data, g, i);
			break ;
		}
		pthread_mutex_unlock(&g->mutex_eat[i]);
		i ++;
	}
}

void	*monitor(void *args)
{
	t_thread_data	*data;
	t_general		*g;
	int				i;

	data = (t_thread_data *)args;
	g = data->general;
	while (1)
	{
		i = 0;
		sub_monitor(data, g, i);
		if (g->eat_times < 1 || g->should_break > 0)
			break ;
		i++;
	}
	return (NULL);
}
