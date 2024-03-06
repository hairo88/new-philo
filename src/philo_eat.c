/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:44:05 by apple             #+#    #+#             */
/*   Updated: 2024/03/01 20:44:52 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int set_fork(t_philo *philo)
{
	t_program   *info;
	int			id;

	info = philo->info;
	id = philo->id;
	if (id % 2 == 0)
	{
		philo->r_fork = &info->forks[id];
		philo->l_fork = &info->forks[(id + 1) % info->num_of_philos];
	}
	else
	{
		philo->r_fork = &info->forks[(id + 1) % info->num_of_philos];
		philo->l_fork = &info->forks[id];
	}
	return (NO_ERROR);
}

int	take_fork(t_philo *phil)
{
	pthread_mutex_lock(phil->r_fork);
	printf("Philosopher [%d] has taken right fork\n", phil->id);
	pthread_mutex_lock(phil->l_fork);
	printf("Philosopher [%d] has taken left fork\n", phil->id);
	return (NO_ERROR);
}