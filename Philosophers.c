/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreamerlino <andreamerlino@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:33:47 by andreamerli       #+#    #+#             */
/*   Updated: 2024/06/15 11:59:49 by andreamerli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(100);
	return (0);
}

int	main(int argc, char **argv)
{
	t_general		g;
	t_thread_data	*data;

	g.should_break = 0;
	g.i = 0;
	if (argc != 6 && argc != 5)
	{
		printf ("Error\n");
		return (0);
	}
	g.i = checker(&g, argv, argc);
	if (g.i != 1)
		return (0);
	data = ft_calloc(sizeof(t_thread_data) * g.g[0], 1);
	set_philo(&g, data, argc);
	set_threads(&g, data, argc);
	destroy_free(&g, data);
}
