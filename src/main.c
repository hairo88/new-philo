/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 00:16:15 by apple             #+#    #+#             */
/*   Updated: 2024/03/01 00:45:40 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char *av[])
{
	t_program   *info_data;
	int			error_flag;

	error_flag = NO_ERROR;
	if (ac != 5 && ac != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	info_data = init_program(ac, av, &error_flag);
	if (error_flag != NO_ERROR)
	{
		printf("Error: failed to initialize philosophers\n");
		return (ERROR);
	}
	printf("error_flag: %d\n", error_flag);
	if (init_philo(info_data) == NO)
	{
		printf("Error: failed to initialize philosophers\n");
		return (ERROR);
	}
	if (start_simulation(info_data))
	{
		printf("Error: failed to start simulation\n");
		return (1);
	}
	(void)info_data;
	return (0);
}

// 5 800 800 200 
