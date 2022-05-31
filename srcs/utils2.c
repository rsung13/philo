/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsung <rsung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:02:45 by rsung             #+#    #+#             */
/*   Updated: 2022/05/31 11:34:06 by rsung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	taking_forks2(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->total_fork[philo->my_fork]);
	pthread_mutex_lock(&philo->data->full_mutex);
	if (check_death(philo) == 1 || philo->data->full \
	>= philo->data->number_of_philo)
	{
		pthread_mutex_unlock(&philo->data->total_fork[philo->my_fork]);
		pthread_mutex_unlock(&philo->data->full_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->full_mutex);
	philo_action(philo, "is taking a fork");
	pthread_mutex_lock(&philo->data->total_fork[philo->other_fork]);
	pthread_mutex_lock(&philo->data->full_mutex);
	if (check_death(philo) == 1 || philo->data->full \
	>= philo->data->number_of_philo)
	{
		pthread_mutex_unlock(&philo->data->total_fork[philo->my_fork]);
		pthread_mutex_unlock(&philo->data->total_fork[philo->other_fork]);
		pthread_mutex_unlock(&philo->data->full_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->full_mutex);
	philo_action(philo, "is taking another fork");
	return (0);
}

int	is_full(t_philo *philo_array, t_data *info)
{
	size_t	i;

	i = 0;
	while (i < info->number_of_philo)
	{
		pthread_mutex_lock(&info->eat_mutex);
		if (philo_array[i].nb_of_meal >= info->times_each_philo_must_eat + 1)
		{
			pthread_mutex_lock(&info->full_mutex);
			info->full++;
			pthread_mutex_unlock(&info->full_mutex);
		}
		pthread_mutex_unlock(&info->eat_mutex);
		i++;
	}
	if (info->full >= info->number_of_philo)
		return (1);
	return (0);
}

int	death_full_check(t_philo *philo_array, t_data *info)
{
	while (1)
	{
		if (is_dead(philo_array, info) == 1)
			return (1);
		if ((int)info->times_each_philo_must_eat != -1)
		{
			if (is_full(philo_array, info) == 1)
				return (1);
		}
	}
	return (0);
}

void	*routine_solo(void *a)
{
	t_philo		*philo;
	long long	temp;

	philo = (t_philo *)a;
	if (philo->data->number_of_philo == 1)
	{
		temp = time_time(timestamp(), philo->data->start);
		printf("[%lldms] ", temp);
		printf("Philo 1 is taking a fork\n");
		usleep((int)philo->data->time_to_die * 1000);
	}
	return (NULL);
}

int	check_check(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
