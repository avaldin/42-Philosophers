/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:37:30 by avaldin           #+#    #+#             */
/*   Updated: 2024/09/30 09:57:36 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	wait_the_end(t_data *data)
{
	long	time;
	int		eating;
	int		i;

	i = 0;
	eating = data->c_philo;
	while (get_status(data) == ALIVE)
	{
		pthread_mutex_lock(&data->philo[i].m_eat);
		time = my_gettimeofday(data) - data->philo[i].last_eat;
		pthread_mutex_unlock(&data->philo[i].m_eat);
		eating -= eat_enought(&data->philo[i], data, eating);
		time_to_die(&data->philo[i], data, time);
		if (i >= data->c_philo - 1)
			i = 0;
		else
			i++;
	}
}

long	my_gettimeofday(t_data *data)
{
	long	time;
	int		secu;

	secu = gettimeofday(&data->time, NULL);
	pthread_mutex_lock(&data->m_time);
	time = data->time.tv_usec / 1000
		+ data->time.tv_sec * 1000 - data->t_start;
	pthread_mutex_unlock(&data->m_time);
	if (!secu)
		return (time);
	return (-1);
}

void	thrend(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->c_philo)
	{
		if (pthread_join(data->philo[i].philo, NULL))
			exit(1);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (-1);
	init_data(argv, argc, &data);
	start(&data);
	thrend(&data);
	clean_exit(&data);
	return (0);
}
