/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:51:21 by avaldin           #+#    #+#             */
/*   Updated: 2024/02/26 16:41:35 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

long	eat(t_philo *philo, long last_eat)
{
	if (!philo->p_num % 2)
		last_eat = take_forks(philo->p_num, philo->next->fork, philo->fork, philo->data);
	else
		last_eat = take_forks(philo->p_num, philo->fork, philo->next->fork, philo->data);
	if (philo->data->c_philo > 1)
	{
		printf("%ld %d is eating\n", last_eat, philo->p_num + 1);
		usleep(1000 * philo->data->t_eat);
		if (pthread_mutex_unlock(philo->next->fork))
			clean_exit(philo->data);
	}
	if (pthread_mutex_unlock(philo->fork))
		clean_exit(philo->data);
	return (last_eat);
}

bool	wait_to_eat(t_philo *philo, t_data *data)
{
	philo->last_eat = eat(philo, philo->last_eat);
	my_gettimeofday(data->time);
	printf("last eat %ld\n", philo->last_eat);
	if (data->time->tv_usec - philo->last_eat >= data->t_die)
	{
		printf("%ld %d died 1\n", data->time->tv_usec - philo->data->t_start, philo->p_num + 1);
		philo->p_status = DEAD;
		philo->data->status = DEAD;
		return (0);
	}
	else if (philo->last_eat == philo->data->t_start)
		return (0);
	return (1);
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

void	*life(void *arg)
{
	t_philo			*philo;
	t_data			*data;
	struct timeval	*time;

	data = (t_data *)arg;
	philo = find_the_philo(data);
	time = data->time;
	pthread_mutex_lock(&data->init);
	pthread_mutex_unlock(&data->init);
	my_gettimeofday(data->time);
	philo->last_eat = data->t_start;
	printf("philo %d started at %ld\n",philo->p_num + 1,data->time->tv_usec - data->t_start);
	while (philo->p_status == ALIVE && data->status == ALIVE)
	{
		if (wait_to_eat(philo, data) == SUCCES)
		{
			my_gettimeofday(data->time);
			printf("%ld %d is sleeping\n",
				   time->tv_usec - data->t_start,
				   philo->p_num + 1);
			usleep(1000 * data->t_sleep);
			my_gettimeofday(data->time);
			printf("%ld %d is thinking\n",
				   (time->tv_usec - data->t_start),
				   philo->p_num + 1);
		}
	}
	return (NULL);
}

void	start(t_data *data)
{
	int 			i;
	t_philo			*philo;

	philo = data->p_first;
	i = data->c_philo;
	data->starter_c = 0;
	my_gettimeofday(data->time);
	data->t_start = data->time->tv_usec;
	my_gettimeofday(data->time);
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
	pthread_mutex_unlock(&data->init);
}