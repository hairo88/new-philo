/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 23:07:37 by apple             #+#    #+#             */
/*   Updated: 2024/03/21 14:33:16 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

# define YES 0
# define NO 1

# define ALIVE 0
# define DEAD 4

# define NO_ERROR 0
# define INVALID_ARG -1
# define ERROR -1

# define FORK 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3

# define    NUM 1
# define DIE 2
# define EAT 3
# define SLEEP 4
# define TIME_EAT 5

typedef struct s_program t_program;

typedef struct s_philo
{
	pthread_t		threrad;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	meal_lock;
	t_program		*info;
}			t_philo;

typedef struct s_program
{
	int				num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_times_to_eat;
	size_t			start_time;
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	last_meal_lock;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}	t_program;

// phlio_utilis.c
int 		ft_philo_atoi(const char* str, int *flag);
size_t		get_time(void);
void		drop_forks(t_philo *philo);
int			ft_usleep(size_t time_in_ms);
int			print_log(t_philo *philo, int log_type);
int			check_philo(t_philo	*philo);
void		update_last_meal(t_philo *philo);

// philo_init.c
t_program	*init_program(int ac, char *av[]);
int			init_philo(t_program *info);
void		program_output(t_program *info);
void		philo_output(t_philo *philo);

// philo.c
int			start_simulation(t_program *info);
void		*monitor_routine(void *arg);
int			try_get_forks(t_philo *philo);

// all_free.c
void	free_all(t_program *info, t_philo *philo);

#endif
