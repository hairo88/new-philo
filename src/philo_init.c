/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:52:29 by apple             #+#    #+#             */
/*   Updated: 2024/03/07 11:06:57 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	program_output(t_program *info)
{
	printf("---info---\n");
	printf("Number of philosophers: %d\n", info->num_of_philos);
	printf("Time to die: %zu\n", info->time_to_die);
	printf("Time to eat: %zu\n", info->time_to_eat);
	printf("Time to sleep: %zu\n", info->time_to_sleep);
	printf("Number of times to eat: %d\n", info->num_times_to_eat);
	printf("---------\n");
}

void	philo_output(t_philo *philo)
{
	size_t	i;

	i = 0;
	printf("---philo---\n");
	while ((int)i < philo->info->num_of_philos)
	{
		printf("Philosopher [%d]\n", philo[i].id);
		printf("Eating: %d\n", philo[i].eating);
		printf("Meals eaten: %d\n", philo[i].meals_eaten);
		printf("Last meal: %zu\n", philo[i].last_meal);
		i++;
	}
	printf("-------\n");
}

t_program *init_program(int ac, char *av[])
{
	t_program   *info_data;
	size_t		i;
	int			error_flag;

	error_flag = NO_ERROR;
	info_data = malloc(sizeof(t_program));
	if (info_data == NULL)
	{
		printf("Error: failed to allocate memory for program data\n");
		return (NULL);
	}
	info_data->num_of_philos = ft_philo_atoi(av[1], &error_flag);
	info_data->time_to_die = ft_philo_atoi(av[2], &error_flag);
	info_data->time_to_eat = ft_philo_atoi(av[3], &error_flag);
	info_data->time_to_sleep = ft_philo_atoi(av[4], &error_flag);
	info_data->start_time = get_time();
	if (ac == 6)
		info_data->num_times_to_eat = ft_philo_atoi(av[5], &error_flag);
	else
		info_data->num_times_to_eat = -1;
	if (error_flag == INVALID_ARG)
		return (NULL);
	info_data->dead_flag = ALIVE;
	if (pthread_mutex_init(&info_data->dead_lock, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&info_data->last_meal_lock, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&info_data->write_lock, NULL) != 0)
		return (NULL);
	info_data->forks = malloc(sizeof(pthread_mutex_t) * info_data->num_of_philos);
	if (info_data->forks == NULL)
		return (NULL);
	i = 0;
	while ((int)i < info_data->num_of_philos)
	{
		if (pthread_mutex_init(&info_data->forks[i], NULL) != 0)
			return (NULL);
		i++;
	}
	return (info_data);
}

int init_philo(t_program *info)
{
	t_philo *philo;
	size_t	i;

	i = 0;
	philo = malloc(sizeof(t_philo) * info->num_of_philos);
	if (philo == NULL)
		return (NO);
	info->philo = philo;
	while ((int)i < info->num_of_philos)
	{
		philo[i].id = i;
		philo[i].eating = NO;
		philo[i].meals_eaten = 0;
		philo[i].dead = &info->dead_flag;
		philo[i].info = info;
		philo[i].last_meal = info->start_time;
		philo[i].dead_lock = &info->dead_lock;
		philo[i].r_fork = &info->forks[i];
		philo[i].l_fork = &info->forks[(i + 1) % info->num_of_philos];
		if (philo[i].r_fork == NULL || philo[i].l_fork == NULL)
			return (NO);
		i++;
	}
	return (YES);
}
