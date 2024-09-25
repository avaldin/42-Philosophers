/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:36:39 by avaldin           #+#    #+#             */
/*   Updated: 2024/09/25 15:49:24 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	take_forks(t_philo *philo, t_data *data)
{
	if (philo->p_num % 2 == 0)
	{
		while (fork_try_take(&philo->fork[1]) == false)
			usleep(10);
		m_printf("has taken a fork", philo->p_num, data);
		while (fork_try_take(&philo->fork[0]) == false)
			usleep(10);
		m_printf("has taken a fork", philo->p_num, data);
	}
	else
	{
		while (fork_try_take(&philo->fork[0]) == false)
			usleep(10);
		m_printf("has taken a fork", philo->p_num, data);
		while (fork_try_take(&philo->fork[1]) == false)
			usleep(10);
		m_printf("has taken a fork", philo->p_num, data);
	}
}

void	*let_him_die(t_philo *philo, t_data *data)
{
	if (pthread_mutex_lock(&data->fork[0].mutex))
		clean_exit(data);
	printf("%ld %d has taken a fork\n",
		my_gettimeofday(data), philo->p_num + 1);
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
