/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:51:43 by avaldin           #+#    #+#             */
/*   Updated: 2024/09/30 11:15:36 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	mutex_destroyer(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->c_philo)
		pthread_mutex_destroy(&data->fork[i].mutex);
	pthread_mutex_destroy(&data->init);
	pthread_mutex_destroy(&data->m_print);
	pthread_mutex_destroy(&data->m_time);
	pthread_mutex_destroy(&data->m_status);
}

void	clean_exit(t_data *data)
{
	mutex_destroyer(data);
	exit(2);
}

void	init_table(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->c_philo - 1)
	{
		pthread_mutex_init(&data->fork[i].mutex, NULL);
		data->philo[i].p_num = i;
		data->philo[i].status = ALIVE;
		i++;
	}
	data->fork[data->c_philo + 1] = data->fork[0];
	data->philo[i].p_num = i;
	data->philo[i].status = ALIVE;
	pthread_mutex_init(&data->fork[i].mutex, NULL);
}

void	init_data(char **argv, int argc, t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->c_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->c_end = ft_atoi(argv[5]);
	if (data->c_philo < 1 || data->c_philo > 200 || data->t_die < 1
		|| data->t_eat < 0 || data->t_sleep < 0 || (argc == 6
			&& data->c_end < 1))
	{
		printf("bad arguments\n");
		exit(3);
	}
	init_table(data);
	data->status = ALIVE;
	pthread_mutex_init(&data->init, NULL);
	pthread_mutex_init(&data->m_print, NULL);
	pthread_mutex_init(&data->m_time, NULL);
	pthread_mutex_init(&data->m_status, NULL);
}
