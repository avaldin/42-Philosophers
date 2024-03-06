/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:52:29 by avaldin           #+#    #+#             */
/*   Updated: 2024/03/06 10:06:50 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	pars_data(t_data *data, char **argv, int argc)
{
	data->c_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->c_end = ft_atoi(argv[5]);
	else
		data->c_end = -1;
	if (data->c_philo < 1 || data->t_die < 1
		|| data->t_eat < 0 || data->t_sleep < 0)
	{
		free(data->time);
		free(data);
		printf("bad arguments\n");
		exit(3);
	}
}
