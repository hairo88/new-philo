/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:15:58 by apple             #+#    #+#             */
/*   Updated: 2024/03/11 19:01:07 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_program *info, t_philo *philo)
{
	size_t	i;

	i = 0;
	while ((int)i < info->num_of_philos)
	{
		pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&info->dead_lock);
	pthread_mutex_destroy(&info->last_meal_lock);
	pthread_mutex_destroy(&info->write_lock);
	free(info->forks);
	free(philo);
	free(info);
}