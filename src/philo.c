/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 00:22:33 by apple             #+#    #+#             */
/*   Updated: 2024/03/06 17:58:58 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void*	philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_philo(philo) == DEAD)
			return (NULL);
		print_log(philo, THINKING);
		if (try_get_forks(philo) == NO_ERROR)
		{
			print_log(philo, EATING);
			ft_usleep(philo->info->time_to_eat);
			// philo->last_meal = get_time();
			update_last_meal(philo);
			philo->meals_eaten++;
			drop_forks(philo);
			if (philo->info->num_times_to_eat != -1 && philo->meals_eaten == philo->info->num_times_to_eat)
				break ;
		}
		else
		{
			print_log(philo, DEAD);
			return (NULL);
		}
		if (check_philo(philo) == DEAD)
			return (NULL);
		print_log(philo, SLEEPING);
		ft_usleep(philo->info->time_to_sleep);
	}
	return (NULL);
}

int try_get_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->dead_lock);
	if (philo->info->dead_flag == DEAD)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (ERROR);
	}
	pthread_mutex_lock(philo->r_fork);
	print_log(philo, FORK);
	pthread_mutex_lock(philo->l_fork);
	print_log(philo, FORK);
	pthread_mutex_unlock(philo->dead_lock);
	return (NO_ERROR);
}

int start_simulation(t_program *info)
{
	size_t		i;
	pthread_t	monitor;

	i = 0;
	pthread_create(&monitor, NULL, monitor_routine, info);
	while (i < (size_t)info->num_of_philos)
	{
		if (pthread_create(&info->philo[i].threrad, NULL, &philo_routine, &info->philo[i]) != 0)
		{
			printf("Error: failed to create thread\n");
			return (ERROR);
		}
		i++;
	}
	i = 0;
	while (i < (size_t)info->num_of_philos)
	{
		if (pthread_join(info->philo[i].threrad, NULL) != 0)
		{
			printf("Error: failed to join thread\n");
			return (ERROR);
		}
		i++;
	}
	pthread_join(monitor, NULL);
	return (NO_ERROR);
}

void	*monitor_routine(void *arg)
{
	t_program	*info;
	size_t		i;

	i = 0;
	info = (t_program *)arg;
	while (1)
	{
		i = 0;
		while ((int)i < info->num_of_philos)
		{
			pthread_mutex_lock(&info->dead_lock);
			if (info->dead_flag == DEAD)
			{
				pthread_mutex_unlock(&info->dead_lock);
				return (NULL);
			}
			if (get_time() - info->philo[i].last_meal > info->time_to_die)
			{
				print_log(&info->philo[i], DEAD);
				info->dead_flag = DEAD;
				pthread_mutex_unlock(&info->dead_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&info->dead_lock);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}
