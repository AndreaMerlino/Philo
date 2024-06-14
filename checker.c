/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreamerlino <andreamerlino@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:25:27 by andreamerli       #+#    #+#             */
/*   Updated: 2024/06/14 20:33:29 by andreamerli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
				printf ("Invalid input!\n");
				return (24);
			}
		}
		i++;
	}
	return (1);
}

int	max_min(char **argv)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (argv[i])
	{
		temp = argv[i];
		if (((ft_strlen(temp) == 10)
				&& (ft_strncmp(temp, "2147483647", ft_strlen(temp)) > 0))
			|| ft_strlen(temp) > 10)
		{
			printf ("Invalid Input!\n");
			return (100);
		}
		i ++;
	}
	return (0);
}

int	checker(t_general *g, char **argv, int argc)
{
	g->g[0] = string_checker(argv);
	if (g->g[0] != 1)
		return (0);
	g->g[0] = max_min(argv);
	if (g->g[0] != 0)
		return (0);
	while (g->i < 5)
	{
		if (g->i < 4)
			g->g[g->i] = ft_atoi(argv[g->i + 1]);
		else
			if (argc == 6 && g->i == 4)
				g->g[g->i] = ft_atoi(argv[5]);
		g->i ++;
	}
	return (1);
}
