/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:34:50 by avaldin           #+#    #+#             */
/*   Updated: 2024/09/25 14:03:12 by avaldin          ###   ########.fr       */
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
	long time;

	if (get_status(data) == ALIVE)
	{
		time = my_gettimeofday(data);
		pthread_mutex_lock(&data->m_print);
		printf("%ld %d %s\n", time, p_num + 1, str);
		pthread_mutex_unlock(&data->m_print);
	}
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

void	fork_give_back(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork[0].mutex);
	if (philo->fork[0].taken)
		philo->fork[0].taken = false;
	pthread_mutex_unlock(&philo->fork[0].mutex);
	pthread_mutex_lock(&philo->fork[1].mutex);
	if (philo->fork[1].taken)
		philo->fork[1].taken = false;
	pthread_mutex_unlock(&philo->fork[1].mutex);
}
