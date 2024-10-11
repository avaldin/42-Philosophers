/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:34:50 by avaldin           #+#    #+#             */
/*   Updated: 2024/10/11 08:48:06 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	get_status(t_data *data)
{
	int	status;

	pthread_mutex_lock(&data->m_status);
	status = data->status;
	pthread_mutex_unlock(&data->m_status);
	return (status);
}

void	m_printf(char *str, int p_num, t_data *data)
{
	pthread_mutex_lock(&data->m_print);
	if (get_status(data) == ALIVE)
	{
		printf("%ld %d %s\n", my_gettimeofday(data), p_num + 1, str);
	}
	pthread_mutex_unlock(&data->m_print);
}

bool	fork_try_take(t_fork *fork)
{
	bool	available;

	available = false;
	pthread_mutex_lock(&fork->mutex);
	if (!fork->taken)
	{
		available = true;
		fork->taken = true;
	}
	pthread_mutex_unlock(&fork->mutex);
	return (available);
}

void	fork_give_back(t_data *data, int p_num)
{
	int	right_fork;

	right_fork = p_num + 1;
	if (p_num == data->c_philo - 1)
		right_fork = 0;
	pthread_mutex_lock(&data->fork[p_num].mutex);
	if (data->fork[p_num].taken)
		data->fork[p_num].taken = false;
	pthread_mutex_unlock(&data->fork[p_num].mutex);
	pthread_mutex_lock(&data->fork[right_fork].mutex);
	if (data->fork[right_fork].taken)
		data->fork[right_fork].taken = false;
	pthread_mutex_unlock(&data->fork[right_fork].mutex);
}
