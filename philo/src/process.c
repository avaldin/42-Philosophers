/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:51:21 by avaldin           #+#    #+#             */
/*   Updated: 2024/02/28 16:13:00 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	eat(t_philo *philo, long eating_time)
{
	if (is_dead(philo, philo->data))
	{
		give_back_forks(philo, philo->data);
		return (-1);
	}
	printf("%ld %d is eating, last eat = %ld\n", eating_time, philo->p_num + 1, my_gettimeofday(philo->data->time, philo->data->t_start) - philo->last_eat);
	philo->last_eat = eating_time;
	usleep(1000 * philo->data->t_eat);
	give_back_forks(philo, philo->data);
	if (is_dead(philo, philo->data))
		return (-1);
	return (0);
}

t_philo	*find_the_philo(t_data *data)
{
	int		i;
	t_philo	*philo;

	philo = data->p_first;
	if (pthread_mutex_lock(data->p_first->fork))
		clean_exit(data);
	i = data->starter_c;
	while (i > 0)
	{
		philo = philo->next;
		i--;
	}
	data->starter_c++;
	philo->p_status = ALIVE;
	if (pthread_mutex_unlock(data->p_first->fork))
		clean_exit(data);
	return (philo);
}

int	sleep_n_think(t_philo *philo, t_data *data)
{
	printf("%ld %d is sleeping\n",
		   my_gettimeofday(data->time, data->t_start),
		   philo->p_num + 1);
	usleep(1000 * data->t_sleep);
	if (is_dead(philo, data))
		return (-1);
	printf("%ld %d is thinking\n",
		   my_gettimeofday(data->time, data->t_start), philo->p_num + 1);
	if (is_dead(philo, data))
		return (-1);
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
	philo->last_eat = 0;
	if (data->c_philo < 2)
		return (let_him_die(data->p_first, data));
	while (42)
	{
		if (take_forks(philo, data) == -1)
			return (DEAD);
		if (eat(philo, my_gettimeofday(data->time, data->t_start)) == -1)
			return (DEAD);
		if (sleep_n_think(philo, data) == -1)
			return (DEAD);
		printf("inf = %ld, supp = %d\n", my_gettimeofday(data->time, data->t_start) - philo->last_eat, data->t_eat * 2);
		usleep(500);
	}
}

void	start(t_data *data)
{
	int 			i;
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
}