/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:36:39 by avaldin           #+#    #+#             */
/*   Updated: 2024/03/06 12:23:15 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	p_fork(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->m_print);
	if (give_status(data) == ALIVE)
		printf("%ld %d has taken a fork\n",
			my_gettimeofday(data), philo->p_num + 1);
	pthread_mutex_unlock(&data->m_print);
}

void	take_forks(t_philo *philo, t_data *data)
{
	if (philo->p_num % 2 == 0)
	{
		if (pthread_mutex_lock(&philo->next->fork))
			clean_exit(data);
		p_fork(philo, data);
		if (pthread_mutex_lock(&philo->fork))
			clean_exit(data);
		p_fork(philo, data);
	}
	else
	{
		if (pthread_mutex_lock(&philo->fork))
			clean_exit(data);
		p_fork(philo, data);
		if (pthread_mutex_lock(&philo->next->fork))
			clean_exit(data);
		p_fork(philo, data);
	}
}

void	*let_him_die(t_philo *philo, t_data *data)
{
	if (pthread_mutex_lock(&philo->fork))
		clean_exit(philo->data);
	printf("%ld %d has taken a fork\n",
		my_gettimeofday(data), philo->p_num + 1);
	while (42)
	{
		pthread_mutex_lock(&data->m_status);
		if (data->status == DEAD)
		{
			pthread_mutex_unlock(&data->m_status);
			pthread_mutex_unlock(&philo->fork);
			return (0);
		}
		pthread_mutex_unlock(&data->m_status);
		usleep(5000);
	}
}

long	give_back_forks(t_philo *philo, t_data *data)
{
	if (!philo->p_num % 2)
	{
		if (pthread_mutex_unlock(&philo->next->fork))
			clean_exit(data);
		if (pthread_mutex_unlock(&philo->fork))
			clean_exit(data);
	}
	else
	{
		if (pthread_mutex_unlock(&philo->fork))
			clean_exit(data);
		if (pthread_mutex_unlock(&philo->next->fork))
			clean_exit(data);
	}
	return (0);
}
