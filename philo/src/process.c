/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:51:21 by avaldin           #+#    #+#             */
/*   Updated: 2024/09/30 11:01:10 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	eat(t_philo *philo, t_data *data)
{
	long time;

	time = my_gettimeofday(data);
	if (get_status(data) != ALIVE)
	{
		fork_give_back(data, philo->p_num);
		return (-1);
	}
	m_printf("is eating", philo->p_num, data);
	pthread_mutex_lock(&philo->m_eat);
	philo->last_eat = time;
	pthread_mutex_unlock(&philo->m_eat);
	usleep(1000 * data->t_eat);
	pthread_mutex_lock(&philo->m_eat);
	philo->eat_c++;
	pthread_mutex_unlock(&philo->m_eat);
	fork_give_back(data, philo->p_num);
	if (get_status(data) != ALIVE)
		return (-1);
	return (0);
}

int	sleep_n_think(t_philo *philo, t_data *data)
{
	m_printf("is sleeping", philo->p_num, data);
	usleep(1000 * data->t_sleep);
	if (get_status(data) != ALIVE)
		return (-1);
	m_printf("is thinking", philo->p_num, data);
	return (0);
}

void	*life(void *arg)
{
	t_philo			*philo;
	t_data			*data;

	data = (t_data *)arg;
	philo = find_the_philo(data);
	pthread_mutex_lock(&data->init);
	pthread_mutex_unlock(&data->init);
	if (data->c_philo < 2) // todo peut etre data race a cause de cphilo
		return (let_him_die(&data->philo[0], data)); //todo
	if (philo->p_num % 2 != 0)
	{
		m_printf("is thinking", philo->p_num, data);
		usleep(100);
	}
	while (42)
	{
		if (get_status(data) == ALIVE)
			take_forks(philo->p_num, data);
		else
			return (DEAD);
		if (eat(philo, data) == -1)
			return (DEAD);
		if (sleep_n_think(philo, data) == -1)
			return (DEAD);
		usleep(500);
	}
}

void	start(t_data *data)
{
	int				i;

	i = 0;
	pthread_mutex_lock(&data->init);
	while (i < data->c_philo)
	{
		if (pthread_create(&data->philo[i].philo, NULL, life, data))
		{
			printf("pthread_create failed\n");
			clean_exit(data);
		}
		i++;
	}
	usleep(10000);
	gettimeofday(&data->time, NULL);
	data->t_start = data->time.tv_usec / 1000 + data->time.tv_sec * 1000;
	pthread_mutex_unlock(&data->init);
	wait_the_end(data);
}
