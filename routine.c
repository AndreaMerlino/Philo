/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreamerlino <andreamerlino@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:38:32 by andreamerli       #+#    #+#             */
/*   Updated: 2024/06/14 22:48:50 by andreamerli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	routine_fork1(t_general *g, t_thread_data *data)
{
	if (data->number_p % 2 == 0)
		pthread_mutex_lock(&g->mutex_forks[data->number_p]);
	else
	{
		if (data->number_p == (g->g[0] - 1))
			pthread_mutex_lock(&g->mutex_forks[0]);
		else
			pthread_mutex_lock(&g->mutex_forks[data->number_p + 1]);
	}
	return (g->dead);
}

int	routine_fork2(t_general *g, t_thread_data *data)
{
	if (data->number_p % 2 == 0)
	{
		if (data->number_p == (g->g[0] - 1))
			pthread_mutex_lock(&g->mutex_forks[0]);
		else
			pthread_mutex_lock(&g->mutex_forks[data->number_p + 1]);
	}
	else
		pthread_mutex_lock(&g->mutex_forks[data->number_p]);
	return (g->dead);
}

int	routine_put_down(t_general *g, t_thread_data *data)
{
	if (data->number_p % 2 == 0)
		pthread_mutex_unlock(&g->mutex_forks[data->number_p]);
	else
	{
		if (data->number_p == (g->g[0] - 1))
			pthread_mutex_unlock(&g->mutex_forks[0]);
		else
			pthread_mutex_unlock(&g->mutex_forks[data->number_p + 1]);
	}
	if (data->number_p % 2 == 0)
	{
		if (data->number_p == (g->g[0] - 1))
			pthread_mutex_unlock(&g->mutex_forks[0]);
		else
			pthread_mutex_unlock(&g->mutex_forks[data->number_p + 1]);
	}
	else
		pthread_mutex_unlock(&g->mutex_forks[data->number_p]);
	return (g->dead);
}

int	sub_routine(t_general *g, t_thread_data *data)
{
	if (routine_fork1(g, data))
		return (1);
	printf("%llu %d has taken a fork\n",
		get_time() - g->start, data->number_p + 1);
	if (routine_fork2(g, data))
		return (1);
	printf("%llu %d has taken a fork\n",
		get_time() - g->start, data->number_p + 1);
	data->last_meal = get_time();
	pthread_mutex_lock(&g->mutex_eat[data->number_p]);
	printf("%llu %d is eating\n", get_time() - g->start, data->number_p + 1);
	pthread_mutex_unlock(&g->mutex_eat[data->number_p]);
	if (g->dead)
		return (1);
	ft_usleep(g->g[2]);
	if (routine_put_down(g, data))
		return (1);
	printf("%llu %d is sleeping\n", get_time() - g->start, data->number_p + 1);
	ft_usleep(g->g[3]);
	if (g->dead)
		return (1);
	printf("%llu %d is thinking\n", get_time() - g->start, data->number_p + 1);
	return (0);
}

void	*routine(void *arg)
{
	t_thread_data	*data;
	t_general		*g;

	data = (t_thread_data *)arg;
	g = data->general;
	while (g->eat_times >= g->g[0] || data->eat >= 1)
	{
		if (sub_routine (g, data))
			break ;
		data->eat -= 1;
	}
	return (NULL);
}
