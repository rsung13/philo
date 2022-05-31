/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsung <rsung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:53:29 by rsung             #+#    #+#             */
/*   Updated: 2022/05/30 17:39:19 by rsung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_eating(t_philo *philo)
{
	if (check_death(philo) == 1)
		return (1);
	if (taking_forks(philo) == 1)
		return (1);
	pthread_mutex_lock(&philo->data->eat_mutex);
	philo_action(philo, "is eating");
	pthread_mutex_lock(&philo->data->last_meal_mutex);
	philo->last_meal = timestamp();
	philo->nb_of_meal++;
	pthread_mutex_unlock(&philo->data->last_meal_mutex);
	pthread_mutex_unlock(&philo->data->eat_mutex);
	if (time_elapsed(philo, 0) == 1)
	{
		pthread_mutex_unlock(&philo->data->total_fork[philo->other_fork]);
		pthread_mutex_unlock(&philo->data->total_fork[philo->my_fork]);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->total_fork[philo->other_fork]);
	pthread_mutex_unlock(&philo->data->total_fork[philo->my_fork]);
	usleep(30);
	return (0);
}

int	is_eating2(t_philo *philo)
{
	if (check_death(philo) == 1)
		return (1);
	if (taking_forks2(philo) == 1)
		return (1);
	pthread_mutex_lock(&philo->data->eat_mutex);
	philo_action(philo, "is eating");
	pthread_mutex_lock(&philo->data->last_meal_mutex);
	philo->last_meal = timestamp();
	philo->nb_of_meal++;
	pthread_mutex_unlock(&philo->data->last_meal_mutex);
	pthread_mutex_unlock(&philo->data->eat_mutex);
	if (time_elapsed(philo, 0) == 1)
	{
		pthread_mutex_unlock(&philo->data->total_fork[philo->other_fork]);
		pthread_mutex_unlock(&philo->data->total_fork[philo->my_fork]);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->total_fork[philo->my_fork]);
	pthread_mutex_unlock(&philo->data->total_fork[philo->other_fork]);
	usleep(30);
	return (0);
}

int	time_elapsed(t_philo *philosopher, int mode)
{
	long long	i;
	long long	j;

	i = timestamp();
	if (mode == 0)
		j = philosopher->data->time_to_eat;
	else if (mode == 1)
		j = philosopher->data->time_to_sleep;
	while (1)
	{
		pthread_mutex_lock(&philosopher->data->full_mutex);
		if (check_death(philosopher) == 1 || philosopher->data->full \
		>= philosopher->data->number_of_philo)
		{
			pthread_mutex_unlock(&philosopher->data->full_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philosopher->data->full_mutex);
		if (time_time(timestamp(), i) >= j)
			return (0);
		usleep(50);
	}
	return (0);
}

int	is_sleeping(t_philo *philosopher)
{
	pthread_mutex_lock(&philosopher->data->full_mutex);
	if (check_death(philosopher) == 1 || philosopher->data->full \
	>= philosopher->data->number_of_philo)
	{
		pthread_mutex_unlock(&philosopher->data->full_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philosopher->data->full_mutex);
	philo_action(philosopher, "is sleeping");
	if (time_elapsed(philosopher, 1) == 1)
		return (1);
	else
		return (0);
}

int	is_thinking(t_philo *philosopher)
{
	pthread_mutex_lock(&philosopher->data->full_mutex);
	if (check_death(philosopher) == 1 || philosopher->data->full \
	>= philosopher->data->number_of_philo)
	{
		pthread_mutex_unlock(&philosopher->data->full_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philosopher->data->full_mutex);
	philo_action(philosopher, "is thinking");
	return (0);
}
