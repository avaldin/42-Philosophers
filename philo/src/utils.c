/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:27:17 by avaldin           #+#    #+#             */
/*   Updated: 2024/03/06 10:18:44 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	give_status(t_data *data)
{
	int	status;

	pthread_mutex_lock(&data->m_status);
	status = data->status;
	pthread_mutex_unlock(&data->m_status);
	return (status);
}

t_philo	*find_the_philo(t_data *data)
{
	int		i;
	t_philo	*philo;

	philo = data->p_first;
	if (pthread_mutex_lock(&philo->fork))
		clean_exit(data);
	i = data->starter_c;
	while (i > 0)
	{
		philo = philo->next;
		i--;
	}
	data->starter_c++;
	philo->p_status = ALIVE;
	if (pthread_mutex_unlock(&data->p_first->fork))
		clean_exit(data);
	return (philo);
}

int time_to_die(t_philo *philo, t_data *data, long time)
{
	if (time > data->t_die)
	{
		pthread_mutex_lock(&data->m_status);
		data->status = DEAD;
		pthread_mutex_lock(&data->m_print);
		printf("%ld %d died\n", time, philo->p_num + 1);
		pthread_mutex_unlock(&data->m_print);
		pthread_mutex_unlock(&data->m_status);
		return (1);
	}
	return (0);
}

int	eat_enought(t_philo *philo, t_data *data, int eating)
{
	if (philo->p_status != ALIVE)
		return (0);
	pthread_mutex_lock(&philo->m_eat);
	if (data->c_end != -1 && philo->eat_c > data->c_end)
	{
		philo->p_status = SATISFIED;
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


