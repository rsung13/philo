/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsung <rsung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:04:08 by rsung             #+#    #+#             */
/*   Updated: 2022/06/03 14:33:48 by rsung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	int		*tab;
	t_data	info;
	t_philo	*philo_array;

	overflow_check(argv);
	if (check_check(argc, argv) == 1)
	{
		printf("Not valid arguments\n");
		return (0);
	}
	if (argc == 5 || argc == 6)
	{
		philo_array = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
		if (!philo_array)
			return (0);
		tab = set_args(argc, argv);
		init_info(&info, philo_array, tab);
		free(tab);
		free(info.total_fork);
		free(info.td_array);
		free(philo_array);
	}
	else
		invalid_argument();
	return (0);
}
