/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:36:39 by avaldin           #+#    #+#             */
/*   Updated: 2024/03/01 16:10:46 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	eat_enought(t_data *data)
{
	t_philo	*philo;
	int		i;
	int		c_satisfied;

	if (give_status(data) == SATISFIED)
		return (SATISFIED);
	c_satisfied = 0;
	i = data->c_philo;
	philo = data->p_first;
	while (i > 0)
	{
		pthread_mutex_lock(&philo->m_eat);
		if (philo->eat_c >= data->c_end && data->c_end != -1)
			c_satisfied++;
		pthread_mutex_unlock(&philo->m_eat);
		philo = philo->next;
		i--;
	}
	if (c_satisfied == data->c_philo)
	{
		pthread_mutex_lock(&data->m_status);
		data->status = SATISFIED;
		pthread_mutex_unlock(&data->m_status);
		printf("all philosopher eated enought.\n");
		return (SATISFIED);
	}
	return (ALIVE);
}

void	take_forks(t_philo *philo, t_data *data)
{
	if (philo->p_num % 2 == 0)
	{
		if (pthread_mutex_lock(&philo->next->fork))
			clean_exit(data);
		printf("%ld %d has taken a fork\n",
			my_gettimeofday(data), philo->p_num + 1);
		if (pthread_mutex_lock(&philo->fork))
			clean_exit(data);
		printf("%ld %d has taken a fork\n",
			my_gettimeofday(data), philo->p_num + 1);
	}
	else
	{
		if (pthread_mutex_lock(&philo->fork))
			clean_exit(data);
		printf("%ld %d has taken a fork\n",
			my_gettimeofday(data), philo->p_num + 1);
		if (pthread_mutex_lock(&philo->next->fork))
			clean_exit(data);
		printf("%ld %d has taken a fork\n",
			my_gettimeofday(data), philo->p_num + 1);
	}
}

bool	is_dead(t_philo *philo, t_data *data)
{
	long	time;

	pthread_mutex_lock(&philo->m_eat);
	time = my_gettimeofday(data) - philo->last_eat;
	pthread_mutex_unlock(&philo->m_eat);
	if (time > data->t_die)
	{
		printf("%ld %d died\n", time, philo->p_num + 1);
		pthread_mutex_lock(&data->m_status);
		data->status = DEAD;
		pthread_mutex_unlock(&data->m_status);
		return (1);
	}
	else if (give_status(data) == DEAD)
		return (1);
	return (0);
}

void	*let_him_die(t_philo *philo, t_data *data)
{
	if (pthread_mutex_lock(&philo->fork))
		clean_exit(philo->data);
	printf("%ld %d has taken a fork\n",
		my_gettimeofday(data), philo->p_num + 1);
	while (is_dead(philo, data) == 0)
		usleep(5000);
	if (pthread_mutex_unlock(&philo->fork))
		clean_exit(philo->data);
	return (0);
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
