/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsung <rsung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:01:03 by rsung             #+#    #+#             */
/*   Updated: 2022/05/30 20:38:32 by rsung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_info(t_data *info, t_philo *philo_array, int *tab)
{
	info->number_of_philo = tab[0];
	info->time_to_die = tab[1];
	info->time_to_eat = tab[2];
	info->time_to_sleep = tab[3];
	info->times_each_philo_must_eat = tab[4];
	info->dead = 0;
	info->full = 0;
	info->start = (long long)timestamp();
	init_philo(info, philo_array);
	philosophers_fork(info, philo_array);
	multiple_td(info, philo_array);
}

void	init_philo(t_data *info, t_philo *philo_array)
{
	int	i;

	i = 0;
	while (i < (int)info->number_of_philo)
	{
		philo_array[i].philo_id = i + 1;
		philo_array[i].my_fork = i;
		philo_array[i].other_fork = (i + 1) % info->number_of_philo;
		philo_array[i].td = i;
		philo_array[i].data = info;
		philo_array[i].nb_of_meal = 0;
		philo_array[i].last_meal = philo_array[i].data->start;
		i++;
	}
}

int8_t	philosophers_fork(t_data *info, t_philo *philo_array)
{
	int	i;

	i = 0;
	info->total_fork = malloc(sizeof(pthread_mutex_t) * info->number_of_philo);
	if (!info->total_fork)
		return (-1);
	while (i < (int)info->number_of_philo)
	{
		pthread_mutex_init(&info->total_fork[philo_array[i].my_fork], NULL);
		i++;
	}
	pthread_mutex_init(&info->pa_mutex, NULL);
	pthread_mutex_init(&info->eat_mutex, NULL);
	pthread_mutex_init(&info->dead_mutex, NULL);
	pthread_mutex_init(&info->last_meal_mutex, NULL);
	pthread_mutex_init(&info->full_mutex, NULL);
	return (0);
}

pthread_t	*multiple_td(t_data *info, t_philo *philo_array)
{
	int	i;

	i = 0;
	info->td_array = malloc(sizeof(pthread_t) * info->number_of_philo);
	if (!info->td_array)
		return (NULL);
	info->start = timestamp();
	if (info->number_of_philo == 1)
	{
		pthread_create(&info->td_array[philo_array[i].td] \
		, NULL, &routine_solo, &philo_array[i]);
	}
	else
	{
		while ((size_t)i < info->number_of_philo)
		{
			pthread_create(&info->td_array[philo_array[i].td] \
			, NULL, &philo_routine, &philo_array[i]);
			i++;
		}
	}
	death_full_check(philo_array, info);
	end_of_program(info);
	return (info->td_array);
}

void	end_of_program(t_data *info)
{
	int	i;

	i = 0;
	while (i < (int)info->number_of_philo)
	{
		pthread_join(info->td_array[i], NULL);
		i++;
	}
	i = 0;
	usleep(10000);
	while (i < (int)info->number_of_philo)
	{
		pthread_mutex_destroy(&info->total_fork[i]);
		i++;
	}
	pthread_mutex_destroy(&info->pa_mutex);
	pthread_mutex_destroy(&info->eat_mutex);
	pthread_mutex_destroy(&info->dead_mutex);
	pthread_mutex_destroy(&info->last_meal_mutex);
	pthread_mutex_destroy(&info->full_mutex);
}
