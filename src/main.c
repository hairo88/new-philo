/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 00:16:15 by apple             #+#    #+#             */
/*   Updated: 2024/03/07 10:58:03 by apple            ###   ########.fr       */
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
		return (1);
	}
	free_all(info_data, info_data->philo);
	return (0);
}

// 5 800 800 200 
