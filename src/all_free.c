/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:15:58 by apple             #+#    #+#             */
/*   Updated: 2024/03/07 10:45:15 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_program *info, t_philo *philo)
{
	size_t	i;

	i = 0;
	while ((int)i < info->num_of_philos)
	{
		pthread_mutex_destroy(philo[i].l_fork);
		pthread_mutex_destroy(philo[i].r_fork);
		i++;
	}
	pthread_mutex_destroy(&info->dead_lock);
	pthread_mutex_destroy(&info->last_meal_lock);
	free(philo);
	free(info);
}