/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:36:39 by avaldin           #+#    #+#             */
/*   Updated: 2024/09/30 09:18:38 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	take_forks(int p_num, t_data *data)
{
	if (p_num % 2 == 0)
	{
		while (fork_try_take(&data->fork[p_num + 1]) == false)
			usleep(10);
		m_printf("has taken a fork", p_num, data);
		while (fork_try_take(&data->fork[p_num]) == false)
			usleep(10);
		m_printf("has taken a fork", p_num, data);
	}
	else
	{
		while (fork_try_take(&data->fork[p_num]) == false)
			usleep(10);
		m_printf("has taken a fork", p_num, data);
		while (fork_try_take(&data->fork[p_num + 1]) == false)
			usleep(10);
		m_printf("has taken a fork", p_num, data);
	}
}

void	*let_him_die(t_philo *philo, t_data *data)
{
	if (pthread_mutex_lock(&data->fork[0].mutex))
		clean_exit(data);
	pthread_mutex_lock(&data->m_print);
	printf("%ld %d has taken a fork\n",
		my_gettimeofday(data), philo->p_num + 1);
	pthread_mutex_unlock(&data->m_print);
	while (42)
	{
		pthread_mutex_lock(&data->m_status);
		if (data->status == DEAD)
		{
			pthread_mutex_unlock(&data->m_status);
			pthread_mutex_unlock(&data->fork[0].mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->m_status);
		usleep(5000);
	}
}
