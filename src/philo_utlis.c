/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utlis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:53:40 by apple             #+#    #+#             */
/*   Updated: 2024/03/06 17:13:29 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_usleep(size_t time_in_ms)
{
	size_t  start_time;

	start_time = get_time();
	while (get_time() - start_time < time_in_ms)
		usleep(100);
	return (NO_ERROR);
}

int ft_philo_atoi(const char* str, int *flag)
{
	size_t  i;
	long long     rnt_value;

	i = 0;
	rnt_value = 0;
	if (str[i] == '-')
		*flag = INVALID_ARG;
	while (str[i] != '\0' && *flag == NO_ERROR)
	{
		if (str[i] < '0' || str[i] > '9')
			*flag =  INVALID_ARG;
		rnt_value = rnt_value * 10 + (str[i] - '0');
		i++;
	}
	return (rnt_value);
}

size_t get_time(void)
{
	struct timeval	time;
	size_t			time_in_ms;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("Error: failed to get time\n");
		return (ERROR);
	}
	time_in_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (time_in_ms);
}

int	print_log(t_philo *philo, int log_type)
{
	size_t	time;

	time = get_time() - philo->info->start_time;
	pthread_mutex_lock(&philo->info->write_lock);
	// printf("%zu log type = [%d]\n", time, log_type);
	if (log_type == EATING)
		printf("%zu %d is eating\n", time, philo->id);
	else if (log_type == SLEEPING)
		printf("%zu %d is sleeping\n", time, philo->id);
	else if (log_type == THINKING)
		printf("%zu %d is thinking\n", time, philo->id);
	else if (log_type == DEAD)
		printf("%zu %d died\n", time, philo->id);
	else if (log_type == FORK)
		printf("%zu %d has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&philo->info->write_lock);
	return (NO_ERROR);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}
