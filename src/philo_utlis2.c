/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utlis2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:33:49 by apple             #+#    #+#             */
/*   Updated: 2024/03/06 18:55:53 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo(t_philo	*philo)
{
	pthread_mutex_lock(&philo->info->dead_lock);
	if (philo->info->dead_flag == DEAD)
	{
		pthread_mutex_unlock(&philo->info->dead_lock);
		return (DEAD);
	}
	pthread_mutex_unlock(&philo->info->dead_lock);
	return (ALIVE);
}

void	update_last_meal(t_philo *philo)
{
	// pthread_mutex_lock(&philo->info->meal_lock);
	pthread_mutex_lock(&philo->info->last_meal_lock);
	philo->last_meal = get_time();
	// pthread_mutex_unlock(&philo->info->meal_lock);
	pthread_mutex_unlock(&philo->info->last_meal_lock);
}
