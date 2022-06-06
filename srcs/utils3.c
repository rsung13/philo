/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsung <rsung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:52:14 by rsung             #+#    #+#             */
/*   Updated: 2022/06/03 12:17:04 by rsung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	overflow_check(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
			j++;
		if (j > 10)
		{
			printf("Take a long hard look at yourself 🤡\n");
			exit (0);
		}
		i++;
	}
	return ;
}

void	unlock_mutexes(t_philo *philo, int mode)
{
	if (mode == 1)
	{
		pthread_mutex_unlock(&philo->data->total_fork[philo->my_fork]);
		pthread_mutex_unlock(&philo->data->total_fork[philo->other_fork]);
		pthread_mutex_unlock(&philo->data->full_mutex);
	}
	else if (mode == 2)
	{
		pthread_mutex_unlock(&philo->data->eat_mutex);
		pthread_mutex_unlock(&philo->data->total_fork[philo->my_fork]);
		pthread_mutex_unlock(&philo->data->total_fork[philo->other_fork]);
	}
	else if (mode == 3)
	{
		pthread_mutex_unlock(&philo->data->total_fork[philo->my_fork]);
		pthread_mutex_unlock(&philo->data->total_fork[philo->other_fork]);
	}
	else if (mode == 4)
	{
		pthread_mutex_lock(&philo->data->dead_mutex);
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->dead_mutex);
		pthread_mutex_unlock(&philo->data->pa_mutex);
	}
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return (s1[i] - s2[i]);
}
