/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsung <rsung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:50:08 by rsung             #+#    #+#             */
/*   Updated: 2022/05/30 21:03:59 by rsung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <ctype.h>
# include <unistd.h>

typedef struct s_info
{
	size_t			number_of_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				times_each_philo_must_eat;
	size_t			dead;
	size_t			full;
	long long		start;
	pthread_mutex_t	*total_fork;
	pthread_t		*td_array;
	pthread_mutex_t	pa_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	full_mutex;
}		t_data;

typedef struct s_philo
{	
	int			philo_id;
	int			my_fork;
	int			other_fork;
	int			td;
	t_data		*data;
	long long	last_meal;
	int			nb_of_meal;
}		t_philo;

/*
/	UTILS
*/

void			invalid_argument(void);
int				ft_atoi(char *str);
long long		timestamp(void);
long long		time_time(long long first, long long last);

/*
/	PARSING & INIT
*/

void			init_info(t_data *info, t_philo *philo_array, int *tab);
int				*set_args(int argc, char **argv);
pthread_t		*multiple_td(t_data *info, t_philo *philo_array);
int8_t			philosophers_fork(t_data *info, t_philo *philo_array);
void			init_philo(t_data *info, t_philo *philo);

/*
/	THREAD
*/

void			is_alive(void);
void			*philo_routine(void *a);
void			philo_action(t_philo *philosopher, char *str);
int				is_eating(t_philo *philosopher);
int				is_eating2(t_philo *philosopher);
int				time_elapsed(t_philo *philosopher, int mode);
int				is_sleeping(t_philo *philosopher);
int				is_thinking(t_philo *philosopher);
void			end_of_program(t_data *info);
int				is_dead(t_philo *philosopher, t_data *info);
int				check_death(t_philo *philo);
int				taking_forks(t_philo *philo);
int				taking_forks2(t_philo *philo);
int				is_full(t_philo *philo_array, t_data *info);
int				death_full_check(t_philo *philo_array, t_data *info);

/*
/	SOLO
*/

void			*routine_solo(void *a);
int				check_check(char **argv);

#endif
