/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsung <rsung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:44:27 by rsung             #+#    #+#             */
/*   Updated: 2022/06/03 12:29:24 by rsung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo_routine(void *a)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)a;
	while (1)
	{
		if (check_death(philosopher) == 1)
			break ;
		if (philosopher->philo_id % 2 == 1)
		{
			if (philosopher->data->number_of_philo % 2 == 1)
				usleep(20000);
			if (is_eating(philosopher) == 1)
				break ;
		}
		else
			if (is_eating2(philosopher) == 1)
				break ;
		if (is_sleeping(philosopher) == 1)
			break ;
		if (is_thinking(philosopher) == 1)
			break ;
		usleep(50);
	}
	return (NULL);
}

void	philo_action(t_philo *philosopher, char *str)
{
	pthread_mutex_lock(&philosopher->data->full_mutex);
	if (philosopher->data->full >= philosopher->data->number_of_philo)
	{
		pthread_mutex_unlock(&philosopher->data->full_mutex);
		return ;
	}
	pthread_mutex_unlock(&philosopher->data->full_mutex);
	if (check_death(philosopher) == 1)
		return ;
	pthread_mutex_lock(&philosopher->data->pa_mutex);
	if (check_death(philosopher) == 1)
	{
		pthread_mutex_unlock(&philosopher->data->pa_mutex);
		return ;
	}
	printf("[%llims] ", time_time(timestamp(), philosopher->data->start));
	printf("Philo %d ", philosopher->philo_id);
	printf("%s\n", str);
	if (ft_strncmp(str, "is dead", 8) != 0)
		pthread_mutex_unlock(&philosopher->data->pa_mutex);
	else
		unlock_mutexes(philosopher, 4);
	usleep(30);
}

int	is_dead(t_philo *philo_array, t_data *info)
{
	size_t	i;

	i = 0;
	while (i < info->number_of_philo)
	{
		pthread_mutex_lock(&info->last_meal_mutex);
		if (time_time(timestamp(), philo_array[i].last_meal) \
		> (long long)info->time_to_die)
		{
			pthread_mutex_unlock(&info->last_meal_mutex);
			philo_action(&philo_array[i], "is dead");
			return (1);
		}
		pthread_mutex_unlock(&info->last_meal_mutex);
		usleep(50);
		i++;
	}
	return (0);
}

int	taking_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->total_fork[philo->other_fork]);
	pthread_mutex_lock(&philo->data->full_mutex);
	if (check_death(philo) == 1 || philo->data->full \
	>= philo->data->number_of_philo)
	{
		pthread_mutex_unlock(&philo->data->full_mutex);
		pthread_mutex_unlock(&philo->data->total_fork[philo->other_fork]);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->full_mutex);
	philo_action(philo, "is taking a fork");
	pthread_mutex_lock(&philo->data->total_fork[philo->my_fork]);
	pthread_mutex_lock(&philo->data->full_mutex);
	if (check_death(philo) == 1 || philo->data->full \
	>= philo->data->number_of_philo)
	{
		unlock_mutexes(philo, 1);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->full_mutex);
	philo_action(philo, "is taking another fork");
	return (0);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_mutex);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
	return (0);
}
