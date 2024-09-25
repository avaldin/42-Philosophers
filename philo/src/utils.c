/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:27:17 by avaldin           #+#    #+#             */
/*   Updated: 2024/09/25 15:42:50 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

t_philo	*find_the_philo(t_data *data)
{
	int		i;

	if (pthread_mutex_lock(&data->fork[0].mutex))
		clean_exit(data);
	i = data->starter_c;
	data->starter_c++;
	if (pthread_mutex_unlock(&data->fork[0].mutex))
		clean_exit(data);
	return (&data->philo[i]);
}

int	time_to_die(t_philo *philo, t_data *data, long time)
{
	if (time > data->t_die)
	{
		pthread_mutex_lock(&data->m_status);
		data->status = DEAD;
		pthread_mutex_unlock(&data->m_status);
		pthread_mutex_lock(&data->m_print);
		printf("%ld %d is dead\n", time, philo->p_num + 1);
		pthread_mutex_unlock(&data->m_print);
		return (1);
	}
	return (0);
}

int	eat_enought(t_philo *philo, t_data *data, int eating)
{
	if (philo->status != ALIVE)
		return (0);
	pthread_mutex_lock(&philo->m_eat);
	if (data->c_end != 0 && philo->eat_c > data->c_end)
	{
		philo->status = SATISFIED;
		if (eating - 1 <= 0)
		{
			pthread_mutex_lock(&data->m_status);
			data->status = SATISFIED;
			pthread_mutex_unlock(&data->m_status);
		}
		pthread_mutex_unlock(&philo->m_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->m_eat);
	return (0);
}
