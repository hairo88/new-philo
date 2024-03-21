/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 00:22:33 by apple             #+#    #+#             */
/*   Updated: 2024/03/21 14:49:27 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void*	philo_routine(void *arg)
{
	t_philo	*philo;

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
			update_last_meal(philo);
			pthread_mutex_lock(&philo->meal_lock);
			philo->meals_eaten++;
			pthread_mutex_unlock(&philo->meal_lock);
			drop_forks(philo);
			if (check_philo(philo) == DEAD)
				return (NULL);
			print_log(philo, SLEEPING);
			ft_usleep(philo->info->time_to_sleep);
			pthread_mutex_lock(&philo->meal_lock);
			if (philo->meals_eaten == philo->info->num_times_to_eat)
			{
				pthread_mutex_unlock(&philo->meal_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&philo->meal_lock);
		}
		else
			return (NULL);
		if (check_philo(philo) == DEAD)
			return (NULL);
	}
	return (NULL);
}

void	philo_one(t_philo *philo)
{
	print_log(philo, FORK);
	ft_usleep(philo->info->time_to_die);
}

int try_get_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (philo->info->dead_flag == DEAD)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (ERROR);
	}
	if (philo->info->num_of_philos == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		philo_one(philo);
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

void    *monitor_routine(void *arg)
{
	t_program	*info;
	size_t		i;

	info = (t_program *)arg;
	while (1)
	{
		i = 0;
		while ((int)i < info->num_of_philos)
		{
			pthread_mutex_lock(&info->philo[i].info->last_meal_lock);
			if (get_time() - info->philo[i].last_meal > info->time_to_die)
			{
				pthread_mutex_unlock(&info->philo[i].info->last_meal_lock);
				pthread_mutex_lock(&info->dead_lock);
				if (info->dead_flag == ALIVE)
				{
					pthread_mutex_unlock(&info->dead_lock);
					print_log(&info->philo[i], DEAD);
					pthread_mutex_lock(&info->dead_lock);
					info->dead_flag = DEAD;
					pthread_mutex_unlock(&info->dead_lock);
				}
				pthread_mutex_unlock(&info->dead_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&info->philo[i].info->last_meal_lock);
			i++;
		}
		usleep(200);
	}
	return (NULL);
}

//  void    *monitor_routine(void *arg)
// {
// 	t_program	*info;
// 	size_t		i;

// 	info = (t_program *)arg;
// 	while (1)
// 	{
// 		i = 0;
// 		while ((int)i < info->num_of_philos)
// 		{
// 			pthread_mutex_lock(&info->dead_lock);
// 			if (info->dead_flag == DEAD)
// 			{
// 				pthread_mutex_unlock(&info->dead_lock);
// 				return (NULL);
// 			}
// 			pthread_mutex_unlock(&info->dead_lock);

// 			pthread_mutex_lock(&info->philo[i].info->last_meal_lock);
// 			if (get_time() - info->philo[i].last_meal > info->time_to_die)
// 			{
// 				pthread_mutex_lock(&info->dead_lock);
// 				if (info->dead_flag == ALIVE)
// 				{
// 					print_log(&info->philo[i], DEAD);
// 					info->dead_flag = DEAD;
// 				}
// 				pthread_mutex_unlock(&info->dead_lock);
// 				pthread_mutex_unlock(&info->philo[i].info->last_meal_lock);
// 				return (NULL);
// 			}
// 			pthread_mutex_unlock(&info->philo[i].info->last_meal_lock);
// 			i++;
// 		}
// 		usleep(200);
// 	}
// 	return (NULL);
// }