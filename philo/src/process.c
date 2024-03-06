/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:51:21 by avaldin           #+#    #+#             */
/*   Updated: 2024/03/06 10:17:01 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	eat(t_philo *philo, long eating_time)
{
	if (give_status(philo->data) != ALIVE)
	{
		give_back_forks(philo, philo->data);
		return (-1);
	}
	pthread_mutex_lock(&philo->data->m_print);
	printf("%ld %d is eating\n", eating_time, philo->p_num + 1);
	pthread_mutex_unlock(&philo->data->m_print);
	usleep(1000 * philo->data->t_eat);
	pthread_mutex_lock(&philo->m_eat);
	philo->eat_c++;
	philo->last_eat = eating_time;
	pthread_mutex_unlock(&philo->m_eat);
	give_back_forks(philo, philo->data);
	if (give_status(philo->data) != ALIVE)
		return (-1);
	return (0);
}

int	sleep_n_think(t_philo *philo, t_data *data)
{
	if (give_status(data) != ALIVE)
		return (-1);
	pthread_mutex_lock(&data->m_print);
	printf("%ld %d is sleeping\n",
		my_gettimeofday(data),
		philo->p_num + 1);
	pthread_mutex_unlock(&data->m_print);
	usleep(1000 * data->t_sleep);
	if (give_status(data) != ALIVE)
		return (-1);
	pthread_mutex_lock(&data->m_print);
	printf("%ld %d is thinking\n",
		my_gettimeofday(data), philo->p_num + 1);
	pthread_mutex_unlock(&data->m_print);
	return (0);
}



void	*life(void *arg)
{
	t_philo			*philo;
	t_data			*data;

	data = (t_data *)arg;
	philo = find_the_philo(data);
	pthread_mutex_lock(&philo->m_eat);
	philo->last_eat = 0;
	pthread_mutex_unlock(&philo->m_eat);
	pthread_mutex_lock(&data->init);
	pthread_mutex_unlock(&data->init);
	if (data->c_philo < 2)
		return (let_him_die(data->p_first, data));
	while (42)
	{
		if (give_status(data) == ALIVE)
			take_forks(philo, data);
		else
			return (DEAD);
		if (eat(philo, my_gettimeofday(data)) == -1)
			return (DEAD);
		if (sleep_n_think(philo, data) == -1)
			return (DEAD);
		usleep(500);
	}
}

void	start(t_data *data)
{
	int				i;
	t_philo			*philo;

	philo = data->p_first;
	i = data->c_philo;
	data->starter_c = 0;
	pthread_mutex_lock(&data->init);
	while (i > 0)
	{
		if (pthread_create(&philo->philo, NULL, life, data))
		{
			printf("pthread_create failed\n");
			clean_exit(data);
		}
		philo = philo->next;
		i--;
	}
	usleep(10000);
	gettimeofday(data->time, NULL);
	data->t_start = data->time->tv_usec / 1000 + data->time->tv_sec * 1000;
	pthread_mutex_unlock(&data->init);
	wait_the_end(data);
}
