/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 00:16:15 by apple             #+#    #+#             */
/*   Updated: 2024/03/11 18:44:18 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char *av[])
{
	t_program   *info_data;

	if (ac != 5 && ac != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	info_data = init_program(ac, av);
	if (info_data == NULL)
	{
		printf("Error: failed to initialize philosophers\n");
		return (ERROR);
	}
	if (init_philo(info_data) == NO)
	{
		printf("Error: failed to initialize philosophers\n");
		return (ERROR);
	}
	if (start_simulation(info_data) == NO)
	{
		printf("Error: failed to start simulation\n");
		return (ERROR);
	}
	free_all(info_data, info_data->philo);
	return (0);
}

__attribute__((destructor))
static void destructor() {
    system("leaks -q philo");
}

// 5 800 800 200 
